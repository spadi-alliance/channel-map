#ifndef CHANNELMAP_CHANNELMAP_H_
#define CHANNELMAP_CHANNELMAP_H_

#include <string>
#include <vector>

// #include "MapElement.hxx"
class IndexTuple;

namespace cmap
{
class ChannelMap {
public:
  static ChannelMap& GetInstance();
  ~ChannelMap();

  void DebugPrint();
  void InitializeFromCSV(const std::string& filepath);

private:
  ChannelMap();
  ChannelMap(const ChannelMap&) = delete;
  ChannelMap& operator=(const ChannelMap&) = delete;

  std::vector<std::string>
  SplitLine(const std::string& str, char delimiter=',');
  // void
  // Set

  // std::mutex mutex_;
  std::vector<std::string> headers_;
  std::vector<std::string> types_;
  std::vector<std::vector<IndexTuple*>> channel_map_;
};

inline ChannelMap&
ChannelMap::GetInstance()
{
  static ChannelMap instance;
  return instance;
}

}
#endif
