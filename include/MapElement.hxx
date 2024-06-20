#ifndef CHANNELMAP_MAPELEMENT_H_
#define CHANNELMAP_MAPELEMENT_H_

#include <map>
#include <vector>
#include <string>
#include <string_view>
#include <mutex>

namespace cmap
{
using MapElementNumberType = uint32_t;
using elnum_t = MapElementNumberType;

class MapElement {
public:
  MapElement(elnum_t number);
  MapElement(std::string_view str);
  operator elnum_t() const;
  operator std::string() const;

  elnum_t get_number(std::string_view str_view);
  const std::string& get_str(elnum_t number) const;

protected:
  elnum_t f_number;
  static std::map<std::string, elnum_t> f_str2int_table;
  static std::vector<std::string> f_int2str_table;
  static std::string f_null_str;
  static std::mutex f_mutex;
};
}

#endif
