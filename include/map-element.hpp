#ifndef CHANNELMAP_MAPELEMENT_H_
#define CHANNELMAP_MAPELEMENT_H_

#include <iostream>
#include <map>
#include <variant>
#include <vector>
#include <string>
#include <string_view>

namespace cmap {

using number_t = uint64_t;
using element_t = std::variant<number_t, std::string>;

}

inline std::ostream&
operator <<(std::ostream& ost, const cmap::element_t& var) {
  std::visit([&ost](const auto& value) {
    ost << value;
  }, var);
  return ost;
}

// class MapElement {
// public:
//   MapElement(number_t number) : m_number(number) {}
//   MapElement(std::string_view str) : m_number(ToNumber(str)) {}
//   operator number_t() const { return m_number; }
//   operator std::string() const { return ToString(m_number); }

//   number_t ToNumber(std::string_view str_view) {
//     std::string str(str_view);
//     auto iter = m_str2int_table.find(str);
//     if (iter == m_str2int_table.end()) {
//       m_str2int_table[str] = m_int2str_table.size();
//       m_int2str_table.push_back(str);
//       return m_int2str_table.size()-1;
//     }
//     return iter->second;
//   }
//   const std::string& ToString(number_t number) const;

// protected:
//   number_t m_number;
//   static std::map<std::string, number_t> m_str2int_table;
//   static std::vector<std::string> m_int2str_table;
//   static std::string m_null_str;
// };

#endif
