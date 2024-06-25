#ifndef CHANNELMAP_INDEXTUPLE_H_
#define CHANNELMAP_INDEXTUPLE_H_

#include <vector>

#include "map-element.hpp"

namespace cmap {

class IndexTuple: public std::vector<element_t> {
public:
  IndexTuple() = default;
  template<typename... Args> IndexTuple(Args... args) {
    this->load(args...);
  }

protected:
  template<typename Head, typename... Tail> void load(Head&& head, Tail&&... tail) {
    this->emplace_back(head);
    this->load(std::forward<Tail>(tail)...);
  }
  void load() {}
};

}

inline std::ostream&
operator <<(std::ostream& ost, const cmap::IndexTuple& tup) {
  ost << "| ";
  for (const auto& e : tup) {
    ost << e;
    if (std::holds_alternative<cmap::number_t>(e)) {
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
