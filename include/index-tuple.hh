#ifndef CHANNELMAP_INDEXTUPLE_H_
#define CHANNELMAP_INDEXTUPLE_H_

#include <vector>

#include "map-element.hh"

namespace cmap {
class IndexTuple: protected std::map<std::string, element_t> {
public:
  IndexTuple() = default;
  // template<typename... Args> IndexTuple(Args... args) {
  //     this->load(args...);
  // }
  void Type(const std::string& str) { m_type = str; }
  const std::string& Type() const { return m_type; }
  using std::map<std::string, element_t>::begin;
  using std::map<std::string, element_t>::end;
  using std::map<std::string, element_t>::size;
  using std::map<std::string, element_t>::empty;
  using std::map<std::string, element_t>::operator[];

protected:
  // template<typename Head, typename... Tail> void
  // load(Head&& head, Tail&&... tail) {
  //     this->emplace_back(head);
  //     this->load(std::forward<Tail>(tail)...);
  // }
  // void load() {}

private:
  std::string m_type;

};

inline std::ostream&
operator <<(std::ostream& ost, const IndexTuple& tup) {
  ost << "[" << tup.Type() << "] ";
  for (const auto& e : tup) {
    ost << e.first << " " << e.second << " | ";
  }
  return ost;
}

}

namespace std {
template<>
struct hash<cmap::IndexTuple> {
  std::size_t operator()(const cmap::IndexTuple& t) const {
    std::size_t h = 0;
    for (const auto& p : t) {
      h ^= std::hash<cmap::element_t>()(p.second);
    }
    return h;
  }
};

}

#endif
