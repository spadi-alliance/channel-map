#ifndef CHANNELMAP_CHANNELMAP_H_
#define CHANNELMAP_CHANNELMAP_H_

#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "index-tuple.hpp"

namespace cmap {

class ChannelMap {
public:
  static ChannelMap& GetInstance();
  ~ChannelMap();

  void DebugPrint();
  void InitializeFromCSV(const std::string& file_path);
  const IndexTuple& Det2Fe(const IndexTuple& fe) const;
  const IndexTuple& Fe2Det(const IndexTuple& det) const;

private:
  ChannelMap();
  ChannelMap(const ChannelMap&) = delete;
  ChannelMap& operator=(const ChannelMap&) = delete;

  void
  MakeTuple(const std::vector<std::string>& tokens);
  std::vector<std::string>
  SplitLine(const std::string& str, char delimiter=',');

  // std::mutex mutex_;
  std::vector<std::string> m_header;
  std::vector<std::string> m_types;
  IndexTuple m_null_tuple;
  std::unordered_set<std::string> m_unique_types;
  // std::unordered_set<std::vector<IndexTuple>> m_tuple_set;
  std::unordered_map<IndexTuple, IndexTuple> m_fe2det_map;
  std::unordered_map<IndexTuple, IndexTuple> m_det2fe_map;
};

inline ChannelMap&
ChannelMap::GetInstance()
{
  static ChannelMap instance;
  return instance;
}

}
#endif
