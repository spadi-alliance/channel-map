#ifndef CHANNELMAP_INDEXTUPLE_H_
#define CHANNELMAP_INDEXTUPLE_H_

#include <vector>

#include "MapElement.hxx"

namespace cmap
{
class IndexTuple: protected std::vector<MapElement> {
  public:
    template<typename... Args> IndexTuple(Args... args) {
        this->load(args...);
    }
    // hash_type hash() const { write your hash function here .... }
  protected:
    template<typename Head, typename... Tail> void
    load(Head&& head, Tail&&... tail) {
        this->emplace_back(head);
        this->load(std::forward<Tail>(tail)...);
    }
    void load() {}
  public:
    using std::vector<MapElement>::begin;
    using std::vector<MapElement>::end;
    using std::vector<MapElement>::size;
    using std::vector<MapElement>::empty;
    using std::vector<MapElement>::operator[];
};

}

#endif
