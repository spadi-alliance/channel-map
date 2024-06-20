#include <cstdlib>
#include <iostream>

#include <channel-map.hh>

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

  auto& channel_map = cmap::ChannelMap::GetInstance();
  channel_map.InitializeFromCSV(input_csv);
  channel_map.DebugPrint();

  return EXIT_SUCCESS;
}
