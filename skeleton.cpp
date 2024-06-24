#include <cstdlib>
#include <iostream>

#include <channel-map.hpp>
#include <index-tuple.hpp>
#include <stopwatch.hpp>

enum EArgs {
  kProcess, kInputCSV, kNArgs
};

int main(int argc, char* argv[]) {
  if (argc < kNArgs) {
    std::cout << "Usage: " << argv[kProcess] << " [InputCSV]" << std::endl;
    return EXIT_SUCCESS;
  }

  std::string input_csv(argv[kInputCSV]);

  auto& channel_map = cmap::ChannelMap::GetInstance();
  channel_map.InitializeFromCSV(input_csv);
  channel_map.DebugPrint();

  {
    cmap::Stopwatch stopwatch;
    cmap::IndexTuple det(170, 30, 0, 262, 0);
    const auto& fe = channel_map.Det2Fe(det);
    std::cout << "det : " << det
              << "-> fe : " << fe << std::endl;
  }

  return EXIT_SUCCESS;
}
