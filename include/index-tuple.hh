#ifndef CHANNELMAP_INDEXTUPLE_H_
#define CHANNELMAP_INDEXTUPLE_H_

#include <vector>

#include "map-element.hh"

namespace cmap
{
class IndexTuple: protected std::map<std::string, element_t> {
public:
  IndexTuple(std::string_view type) : m_type(type) {}
  // template<typename... Args> IndexTuple(Args... args) {
  //     this->load(args...);
  // }
  // hash_type hash() const { write your hash function here .... }
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

#endif
