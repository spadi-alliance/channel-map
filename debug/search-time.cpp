#include <cstdlib>
#include <iostream>

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

  /*
    to be implemented
   */

  return EXIT_SUCCESS;
}
