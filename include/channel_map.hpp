#ifndef CHANNELMAP_CHANNELMAP_H_
#define CHANNELMAP_CHANNELMAP_H_

#include <filesystem>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "index_tuple.hpp"

namespace cmap {

class ChannelMap {
public:
  static ChannelMap& get_instance();
  ~ChannelMap() {}

  void debug_print();
  void initialize(const std::filesystem::path& file_path);
  void initialize_from_csv(const std::string& file_path);
  const IndexTuple& det_to_fe(const IndexTuple& fe) const;
  const IndexTuple& fe_to_det(const IndexTuple& det) const;

private:
  ChannelMap();
  ChannelMap(const ChannelMap&) = delete;
  ChannelMap& operator=(const ChannelMap&) = delete;

  void
  make_tuple(const std::vector<std::string>& tokens);
  std::vector<std::string>
  split_line(const std::string& str, char delimiter=',');

  // std::mutex mutex_;
  const IndexTuple m_null_tuple;
  std::vector<std::string> m_header;
  std::vector<std::string> m_element_type;
  std::unordered_set<std::string> m_unique_types;
  std::unordered_map<IndexTuple, IndexTuple> m_fe2det_map;
  std::unordered_map<IndexTuple, IndexTuple> m_det2fe_map;
};

inline ChannelMap&
ChannelMap::get_instance()
{
  static ChannelMap instance;
  return instance;
}

}
#endif
