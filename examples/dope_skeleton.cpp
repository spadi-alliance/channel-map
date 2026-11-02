#include "chmap/channel_map_dopeness.hpp"

#include <cstdint>
#include <exception>
#include <iostream>
#include <memory>
#include <utility>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " map.csv\n";
        return 1;
    }
    try {
        auto& map = chmap::ChannelMapDopeness::get_instance();
        const double fill_ratio = map.initialize(argv[1], true);
        std::cout << std::dec << "FE fill ratio: " << fill_ratio << '\n';

        // Example from examples/test.csv: 192.168.2.170, CH12.
        // nullptr covers both out-of-range addresses and unmapped slots inside the range.
        const auto* det = map.findDET(2, 170, 12);
        if (!det) {
            std::cerr << "Example FEE channel is not registered in this CSV\n";
            return 2;
        }
        det->decode();

        // Reuse the returned item; no second lookup is needed to access its fields.
        const auto* fe = map.findFE(*det);
        if (!fe) {
            std::cerr << "Inverse mapping is not registered\n";
            return 3;
        }
        fe->decode();

        // String lookup uses: name, plane, segment, readout name, channel number.
        const auto* named_fe = map.findFE(det->getDetectorName(), det->getDetectorPlane(),
                                         det->segment, det->getReadoutChannelName(),
                                         det->channel_number);
        if (!named_fe || !(*named_fe == *fe)) return 4;

        // Independent inverse lookup: resolve user-facing names once during setup.
        // CSV example: t1 / plane 0 / segment 0 / right / channel 0.
        uint8_t name_index = 0;
        uint8_t plane_index = 0;
        uint8_t readout_index = 0;
        if (!map.detname_dictionary.StringToIndex("t1", name_index) ||
            !map.plane_dictionary.StringToIndex("0", plane_index) ||
            !map.readout_channel_dictionary.StringToIndex("right", readout_index)) {
            std::cerr << "Example detector name, plane or readout is not registered\n";
            return 6;
        }

        // Reuse these indices for runtime lookups; no string lookup is performed here.
        const uint8_t segment = 0;
        const uint16_t channel_number = 0;
        const auto* indexed_fe = map.findFE(name_index, plane_index, segment,
                                           readout_index, channel_number);
        if (!indexed_fe) {
            std::cerr << "Example detector channel has no inverse mapping\n";
            return 7;
        }
        if (indexed_fe->ip3rd != 2 || indexed_fe->ip4th != 170 || indexed_fe->ch != 12) {
            std::cerr << "Example inverse mapping does not match the expected FEE address\n";
            return 8;
        }
        indexed_fe->decode();

        // Register drift-chamber geometry during setup, separately from the counter example.
        const auto* dc_fe = map.findFE("dc1", "X", 1, "0", 0);
        if (!dc_fe) return 9;
        const auto* dc_det = map.findDET(*dc_fe);
        if (!dc_det) return 10;
        auto geom = std::make_unique<chmap::GeomItemDC>();
        geom->SetGlobalPosition(0.0, 0.0, 100.0);
        geom->SetResolution(0.1, 0.1, 0.1);
        geom->SetRotationAngles(0.0, 0.0, 0.0);
        geom->SetWireGeometry(1.0, 5.0, 0.0);
        geom->CalcWirePosition(dc_det->channel_number);
        if (!map.setGeometry(*dc_det, std::move(geom))) return 5;

        // Illustrative constants, not measured calibration parameters.
        // drift time [ns] = (TDC - reference TDC) [count] * scale [ns/count] + offset [ns].
        auto tdc_calib = std::make_unique<chmap::CalibrationItem_DCTdcCalib>();
        tdc_calib->SetTdcCalibration(-5.0, 0.5); // offset, scale
        if (!map.setTdcCalibration(*dc_det, std::move(tdc_calib))) return 11;

        // drift length [mm] = c0 + c1 * drift time [ns].
        // SetApproximation takes the number of coefficients, not the polynomial degree.
        auto drift_calib = std::make_unique<chmap::CalibrationItem_DCDriftLength>();
        drift_calib->SetApproximation(2, {0.0, 0.05});
        if (!map.setDriftCalibration(*dc_det, std::move(drift_calib))) return 12;

        // All three parts belong to the map; these are borrowed, read-only pointers.
        // Check the required configuration once during setup, before processing hits.
        const auto* config = dc_det->getConfiguration();
        if (!config) return 13;
        const auto* geometry = config->getGeometry();
        const auto* tdc = config->getTdcCalibration();
        const auto* drift = config->getDriftCalibration();
        if (!geometry || !tdc || !drift) return 14;
        std::cout << "Registered geometry Z: " << geometry->GetGlobalZ() << '\n';
        std::cout << "TDC offset: " << tdc->GetOffset()
                  << ", scale: " << tdc->GetScale() << '\n';
        std::cout << "Drift coefficients (" << std::dec << drift->GetApproximationOrder()
                  << "):";
        for (double coefficient : drift->GetCoefficients())
            std::cout << ' ' << coefficient;
        std::cout << '\n';

        // Example hit calculation, as in the consumer's DCHit processing.
        // Use signed/floating-point subtraction so earlier TDC values do not wrap.
        const double raw_tdc = 120.0;
        const double reference_tdc = 100.0;
        const double drift_time = (raw_tdc - reference_tdc) * tdc->GetScale() + tdc->GetOffset();
        const double drift_length = drift->GetDriftLength(drift_time);
        std::cout << "Example drift time [ns]: " << drift_time
                  << ", drift length [mm]: " << drift_length << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Channel map error: " << e.what() << '\n';
        return 1;
    }
}
