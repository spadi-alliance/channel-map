#ifndef CHANNEL_MAP_H
#define CHANNEL_MAP_H

#include <string>
#include <vector>

// #include "MapElement.hxx"

namespace cmap
{

class ChannelMap {
public:
  static ChannelMap& getInstance();
  ~ChannelMap();

  void debugPrint();
  void initializeFromCSV(const std::string& filepath);

private:
  ChannelMap();
  ChannelMap(const ChannelMap&) = delete;
  ChannelMap& operator=(const ChannelMap&) = delete;

  // std::mutex manager_mutex;
};

inline ChannelMap&
ChannelMap::getInstance()
{
  static ChannelMap instance;
  return instance;
}

}
#endif
