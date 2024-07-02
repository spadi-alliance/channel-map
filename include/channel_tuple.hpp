#ifndef CHANNELMAP_CHANNELTUPLE_H_
#define CHANNELMAP_CHANNELTUPLE_H_

#include <vector>

#include "element.hpp"

namespace chmap {

class ChannelTuple: public std::vector<element_t> {
public:
  ChannelTuple() = default;
  template<typename... Args> ChannelTuple(Args... args) {
    this->set_element(args...);
  }
  void set_title(const std::string& t) { m_types.push_back(t); }
  const std::string& title(std::size_t i) const {
    if (i < m_types.size()) {
      return m_types[i];
    } else {
      static std::string null_str;
      return null_str;
    }
  }

protected:
  template<typename Head, typename... Tail>
  void set_element(Head&& head, Tail&&... tail) {
    this->emplace_back(head);
    this->set_element(std::forward<Tail>(tail)...);
  }
  void set_element() {}

  std::vector<std::string> m_types;
};

}

inline std::ostream&
operator <<(std::ostream& ost, const chmap::ChannelTuple& tup) {
  ost << "| ";
  for (int i=0, n=tup.size(); i<n; ++i) {
    ost << tup.title(i) << " " << tup[i];
    if (std::holds_alternative<chmap::number_t>(tup[i])) {
      ost << "(number) | ";
    } else {
      ost << "(string) | ";
    }
  }
  return ost;
}

namespace std {

/*
  follows the boost::hash_combined method
 */

template<>
struct hash<chmap::ChannelTuple> {
  std::size_t operator()(const chmap::ChannelTuple& t) const {
    std::size_t h = 0;
    const std::size_t golden_ratio = 0x9e3779b97f4a7c15LLU;
    for (const auto& e : t) {
      h ^= std::hash<chmap::element_t>()(e)
        + golden_ratio + (h << 12) + (h >> 4);
    }
    return h;
  }
};

template<>
struct hash<std::vector<chmap::ChannelTuple>> {
  std::size_t operator()(const std::vector<chmap::ChannelTuple>& v) const {
    std::size_t h = 0;
    const std::size_t golden_ratio = 0x9e3779b97f4a7c15LLU;
    for (const auto& t : v) {
      h ^= std::hash<chmap::ChannelTuple>()(t)
        + golden_ratio + (h << 12) + (h >> 4);
    }
    return h;
  }
};

}

#endif
