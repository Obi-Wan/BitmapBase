#ifndef BITMAP_UTILS_H
#define BITMAP_UTILS_H

#include "bitmap_types.h"
#include <deque>
#include <algorithm>

using namespace std;
//#define DEBUG

#ifdef DEBUG
    #include <stdio.h>
#endif


class listChannelCoordinates {
  
  struct nodeChannelCoordinates {
    struct coordinate coordinates;

    uc8 value;

    nodeChannelCoordinates(const coordinate & coords, const uc8 & _value)
          : coordinates(coords), value(_value) { }

    bool operator< (const nodeChannelCoordinates & node) const {
      return (value < node.value);
    }
  };

  deque<nodeChannelCoordinates> list;
  
public:

  listChannelCoordinates() { }

  void addUnsortedElement(const coordinate & coords, const uc8 & value) {
    list.push_front(nodeChannelCoordinates(coords,value));
  }

  bool popMinElementSorted(coordinate & coords, uc8 & value) {
    if (!list.empty()) {
      const nodeChannelCoordinates & node = list.front();
      coords = node.coordinates;
      value = node.value;
      list.pop_front();
      return true;
    } else {
      return false;
    }
  }
  
  void emptyList() { list.clear(); }

  ~listChannelCoordinates() { emptyList(); }

  const ui32 getNumElements() const { return list.size(); }

  void sortList() { sort(list.begin(),list.end()); }

  bool isEmpty() const { return (list.size() == 0); }

  bool isSorted() const {
    for(ui32 i = 0; i < list.size();i++) {
      if (list.at(i).value < list.at(i+1).value) {
        return false;
      }
    }
    return true;
  }
  
};


//--------------------------

//#undef DEBUG

#endif