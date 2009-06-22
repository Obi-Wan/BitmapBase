#ifndef BITMAP_FUNCS_H
#define BITMAP_FUNCS_H

#include "bitmap_types.h"

struct node_channel_coordinate {
  struct coordinate coordinates;

  uc8 value;

  struct node_channel_coordinate * next;
  struct node_channel_coordinate * previous;
};

struct ordered_list_channel_coordinate {
  struct node_channel_coordinate * first;
  struct node_channel_coordinate * last;

  ui32 numElements;
};

inline bool
addOrderedListCCElement(struct ordered_list_channel_coordinate & list,
                        struct coordinate coords, uc8 value) {
  if (list.last < value) {
    list.last->next = &node_channel_coordinate(coords,value,null,list.last);
    list.last = list.last->next;
    return true;
  } else if (list.first > value) {
    list.first->previous = &node_channel_coordinate(coords,value,list.first,null);
    list.first = list.first->previous;
    return true;
  }
  node_channel_coordinate * currentElement = list.first->next;
  for(;currentElement->next != null;currentElement = currentElement->next) {
    if (currentElement->value > value) {
      currentElement->previous = &node_channel_coordinate(coords,value,
                                                          currentElement,
                                                          currentElement->previous);
      currentElement->previous->previous->next = currentElement->previous;
      return true;
    }
  }
  return false;
};

#endif