#ifndef BITMAP_UTILS_H
#define BITMAP_UTILS_H

#include "bitmap_types.h"

typedef struct node_channel_coordinate {
  struct coordinate coordinates;

  uc8 value;

  node_channel_coordinate * next;
  node_channel_coordinate * previous;

  node_channel_coordinate(const coordinate & coords, const uc8 & _value,
                          node_channel_coordinate * _next,
                          node_channel_coordinate * _previous)
        : coordinates(coords), value(_value), next(_next),
          previous(_previous) { }
} node_channel_coordinate;

typedef struct ordered_list_channel_coordinate {
  node_channel_coordinate * first;
  node_channel_coordinate * last;

  ui32 numElements;

  ordered_list_channel_coordinate()
            : first(NULL),last(NULL),numElements(0) { }
} ordered_list_channel_coordinate;

inline ordered_list_channel_coordinate *
createOrderedListCC() {
  return new ordered_list_channel_coordinate();
}

inline bool
addElementOrderedListCC(ordered_list_channel_coordinate & list,
                        const coordinate & coords, const uc8 & value) {
  if (!list.first) {
    list.first = list.last = new node_channel_coordinate(coords,value,NULL,NULL);
    list.numElements++;
    return true;
  } else if (list.last->value < value) {
    list.last->next = new node_channel_coordinate(coords,value,NULL,list.last);
    list.last = list.last->next;
    list.numElements++;
    return true;
  } else if (list.first->value > value) {
    list.first->previous = new node_channel_coordinate(coords,value,list.first,NULL);
    list.first = list.first->previous;
    list.numElements++;
    return true;
  }
  node_channel_coordinate * currentElement = list.first->next;
  for(;currentElement->next != NULL;currentElement = currentElement->next) {
    if (currentElement->value > value) {
      currentElement->previous = new node_channel_coordinate(coords,value,
                                                          currentElement,
                                                          currentElement->previous);
      currentElement->previous->previous->next = currentElement->previous;
      list.numElements++;
      return true;
    }
  }
  return false;
};

inline bool
popMinElementOrderedListCC(ordered_list_channel_coordinate & list,
                           coordinate & coords, uc8 & value) {
  if (list.first != NULL) {
    coords = list.first->coordinates;
    value = list.first->value;
    node_channel_coordinate * tempNode = list.first;
    list.first = tempNode->next;
    list.first->previous = NULL;
    delete tempNode;
    list.numElements--;
    return true;
  } else {
    return false;
  }
};

inline void
destroyOrderedListCC(ordered_list_channel_coordinate * list) {
  for(node_channel_coordinate * temp = list->first->next; temp; temp = temp->next) {
    delete temp->previous;
  }
  delete list->last;
  delete list;
  list = NULL;
};

inline bool
isEmptyOrderedListCC(const ordered_list_channel_coordinate & list) {
  return (list.numElements == 0);
};

//--------------------------


#endif