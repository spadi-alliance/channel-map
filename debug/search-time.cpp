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

  // generate and shuffle key list
  std::vector<chmap::ChannelTuple> keys;
  for (const auto& pair : channel_map.get("fe")) {
    keys.push_back(pair.first);
  }
  std::random_device rd;
  std::mt19937 generator(rd());
  std::shuffle(keys.begin(), keys.end(), generator);

  TFile root_file("search-time.root", "recreate");
  TH1D h1("h1", "search time; nanoseconds; counts", 1000, 0, 20000);

  for (const auto& key : keys) {
    chmap::Stopwatch stopwatch;
    const auto& val = channel_map.get("fe", key);
    stopwatch.stop();
    h1.Fill(stopwatch.elapsed());
    chmap::info << val << std::endl;
  }

  root_file.Write();
  return EXIT_SUCCESS;
}
