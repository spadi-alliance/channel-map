// -*- C++ -*-

#include <cstdlib>
#include <iostream>

#include <ChannelMap.hxx>

enum EArgs {
  kProcess, kInputCSV, kNArgs
};

int main(int argc, char* argv[])
{
  if(argc < kNArgs){
    std::cout << "Usage: " << argv[kProcess] << " [InputCSV]" << std::endl;
    return EXIT_SUCCESS;
  }

  std::string input_csv(argv[kInputCSV]);

  auto& channel_map = cmap::ChannelMap::getInstance();
  channel_map.initializeFromCSV(input_csv);
  channel_map.debugPrint();

  return EXIT_SUCCESS;
}
