#ifndef BITMAP_UTILS_H
#define BITMAP_UTILS_H

#include "bitmap_types.h"
#include <deque>
//#include <algorithm>

using namespace std;
//#define DEBUG

#ifdef DEBUG
    #include <stdio.h>
#endif


class list_channel_coordinate {
  
  struct node_channel_coordinate {
    struct coordinate coordinates;

    uc8 value;

    node_channel_coordinate(const coordinate & coords, const uc8 & _value)
          : coordinates(coords), value(_value) { }

    bool operator< (const node_channel_coordinate & node) {
      return (value < node.value);
    }
  };

  deque<node_channel_coordinate> list;

  list_channel_coordinate() {  }
  
public:
  static list_channel_coordinate * createListCC() {
    return new list_channel_coordinate();
  }

  bool isEmptyListCC() const {
    return (list.size() == 0);
  }

  bool isSortedListCC() const {
    for(ui32 i = 0; i < list.size();i++) {
      if (list.at(i).value < list.at(i+1).value) {
        return false;
      }
    }
    return true;
  }
  
  bool addSortedElementListCC(const coordinate & coords, const uc8 & value) {
    if (list.empty()) {
      list.push_front(node_channel_coordinate(coords,value));
      return true;
    } else if (list.back().value <= value) {
      list.push_back(node_channel_coordinate(coords,value));
      return true;
    } else if (list.front().value >= value) {
      list.push_front(node_channel_coordinate(coords,value));
      return true;
    }
    for(deque<node_channel_coordinate>::iterator iter = list.begin();
            iter < list.end(); iter++) {
      if (iter->value >= value) {
        list.insert(iter,node_channel_coordinate(coords,value));
        return true;
      }
    }
    return false;
  }

  bool popMinElementSortedListCC(coordinate & coords, uc8 & value) {
    if (!list.empty()) {
      const node_channel_coordinate & node = list.front();
      coords = node.coordinates;
      value = node.value;
      list.pop_front();
      return true;
    } else {
      return false;
    }
  }
  
  void emptyList() {
    list.clear();
  }

  ~list_channel_coordinate() {
    emptyList();
  }

  const ui32 getNumElements() const { return list.size(); }

//  void sortList() {
//    sort< deque<node_channel_coordinate> >(list);
//  }
};


//--------------------------

//#undef DEBUG

#endif