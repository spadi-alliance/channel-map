#ifndef CHANNELMAP_INDEXTUPLE_H_
#define CHANNELMAP_INDEXTUPLE_H_

#include <vector>

#include "map-element.hh"

namespace cmap
{
class IndexTuple: protected std::map<std::string, MapElement> {
  public:
    template<typename... Args> IndexTuple(Args... args) {
        this->load(args...);
    }
    // hash_type hash() const { write your hash function here .... }
  protected:
    // template<typename Head, typename... Tail> void
    // load(Head&& head, Tail&&... tail) {
    //     this->emplace_back(head);
    //     this->load(std::forward<Tail>(tail)...);
    // }
    void load() {}
  public:
    using std::map<std::string, MapElement>::begin;
    using std::map<std::string, MapElement>::end;
    using std::map<std::string, MapElement>::size;
    using std::map<std::string, MapElement>::empty;
    using std::map<std::string, MapElement>::operator[];
};

}

#endif
