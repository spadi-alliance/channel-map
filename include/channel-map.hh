#ifndef CHANNELMAP_CHANNELMAP_H_
#define CHANNELMAP_CHANNELMAP_H_

#include <map>
#include <string>
#include <unordered_set>
#include <vector>

// #include "MapElement.hxx"

namespace cmap
{
class IndexTuple;

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

  const IndexTuple*
  MakeTuple(const std::vector<std::string>& tokens);
  std::vector<std::string>
  SplitLine(const std::string& str, char delimiter=',');

  // std::mutex mutex_;
  std::vector<std::string> m_header;
  std::vector<std::string> m_types;
  std::unordered_set<std::string> m_unique_types;
  std::vector<std::vector<const IndexTuple*>> channel_map_;
};

inline ChannelMap&
ChannelMap::GetInstance()
{
  static ChannelMap instance;
  return instance;
}

}
#endif
