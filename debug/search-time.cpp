#include <cstdlib>
#include <iostream>
#include <random>

#include <TFile.h>
#include <TH1.h>

#include <channel_map.hpp>

enum EArgs {
  kProcess, kInputCSV, kNArgs
};

int main(int argc, char* argv[]) {
  if (argc < kNArgs) {
    std::cout << "Usage: " << argv[kProcess] << " [InputCSV]" << std::endl;
    return EXIT_SUCCESS;
  }

  std::string input_csv(argv[kInputCSV]);

  auto& channel_map = chmap::ChannelMap::get_instance();
  channel_map.initialize(input_csv);

  TFile root_file("search-time.root", "recreate");
  TH1D h1("h1", "search time; nanoseconds; counts", 1000, 0, 20000);
  TH1D h2("h2", "average search time; nanoseconds; counts", 1000, 0, 10000);

  for (int i=0; i<1000; ++i) {
    // generate and shuffle key list
    std::vector<chmap::ChannelTuple> keys;
    for (const auto& pair : channel_map.get("fe")) {
      keys.push_back(pair.first);
    }
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(keys.begin(), keys.end(), generator);
    h1.Reset();

    for (const auto& key : keys) {
      chmap::Stopwatch stopwatch;
      const auto& val = channel_map.get("fe", key);
      auto elapsed = stopwatch.elapsed();
      h1.Fill(elapsed);
      // chmap::info << val << std::endl;
    }
    chmap::info << keys.size() << " keys searched "
                << h1.GetMean() << " +/- " << h1.GetStdDev()
                << " nanoseconds"
                << std::endl;
    h2.Fill(h1.GetMean(), 1./h1.GetStdDev());
  }

  root_file.Write();
  return EXIT_SUCCESS;
}
