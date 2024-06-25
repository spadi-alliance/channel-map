#ifndef CHANNELMAP_INDEXTUPLE_H_
#define CHANNELMAP_INDEXTUPLE_H_

#include <vector>

#include "map-element.hpp"

namespace cmap {

class IndexTuple: public std::vector<element_t> {
public:
  IndexTuple() = default;
  template<typename... Args> IndexTuple(Args... args) {
    this->SetElement(args...);
  }
  void SetTitle(const std::string& t) { m_types.push_back(t); }
  const std::string& Title(std::size_t i) const {
    if (i < m_types.size()) {
      return m_types[i];
    } else {
      static std::string null_str;
      return null_str;
    }
  }

protected:
  template<typename Head, typename... Tail>
    void SetElement(Head&& head, Tail&&... tail) {
    this->emplace_back(head);
    this->SetElement(std::forward<Tail>(tail)...);
  }
  void SetElement() {}

  std::vector<std::string> m_types;
};

}

inline std::ostream&
operator <<(std::ostream& ost, const cmap::IndexTuple& tup) {
  ost << "| ";
  for (int i=0, n=tup.size(); i<n; ++i) {
    ost << tup.Title(i) << " " << tup[i];
    if (std::holds_alternative<cmap::number_t>(tup[i])) {
      ost << "(number) | ";
    } else {
      ost << "(string) | ";
    }
  }
  return ost;
}

namespace std {

template<>
struct hash<cmap::IndexTuple> {
  std::size_t operator()(const cmap::IndexTuple& t) const {
    std::size_t h = 0;
    for (const auto& e : t) {
      h ^= std::hash<cmap::element_t>()(e);
    }
    return h;
  }
};

template<>
struct hash<std::vector<cmap::IndexTuple>> {
  std::size_t operator()(const std::vector<cmap::IndexTuple>& v) const {
    std::size_t h = 0;
    for (const auto& t : v) {
      h ^= std::hash<cmap::IndexTuple>()(t);
    }
    return h;
  }
};

}

#endif
