#ifndef BITMAP_UTILS_H
#define BITMAP_UTILS_H

#include "bitmap_types.h"

//#define DEBUG

#ifdef DEBUG
    #include <stdio.h>
#endif


class list_channel_coordinate {
  
  struct node_channel_coordinate {
    struct coordinate coordinates;

    uc8 value;

    node_channel_coordinate * next;
    node_channel_coordinate * previous;

    node_channel_coordinate(const coordinate & coords, const uc8 & _value,
                            node_channel_coordinate * _next,
                            node_channel_coordinate * _previous)
          : coordinates(coords), value(_value), next(_next),
            previous(_previous) { }
  };
  
  node_channel_coordinate * first;
  node_channel_coordinate * last;

  ui32 numElements;

  list_channel_coordinate() : first(NULL),last(NULL),numElements(0) { }
  
public:
  static list_channel_coordinate * createListCC() {
    return new list_channel_coordinate();
  }

  bool isEmptyListCC() const {
    return (numElements == 0);
  }

  bool isSortedListCC() const {
    for(const node_channel_coordinate * temp = first; temp; temp = temp->next) {
      delete temp->previous;
    }
  }
  
  bool addSortedElementListCC(const coordinate & coords, const uc8 & value) {
    if (first == NULL) {
      first = last = new node_channel_coordinate(coords,value,NULL,NULL);
      numElements++;
      return true;
    } else if (last->value <= value) {
      last->next = new node_channel_coordinate(coords,value,NULL,last);
      last = last->next;
      numElements++;
      return true;
    } else if (first->value >= value) {
      first->previous = new node_channel_coordinate(coords,value,first,NULL);
      first = first->previous;
      numElements++;
      return true;
    }
    for(node_channel_coordinate * currentElement = first->next;
        currentElement->next != NULL; currentElement = currentElement->next) {
      if (currentElement->value >= value) {
        node_channel_coordinate * previousElement = currentElement->previous;
        node_channel_coordinate * newElement = new node_channel_coordinate(coords,value,
                                                            currentElement,
                                                            previousElement);
        currentElement->previous = newElement;
        if (previousElement) {
          previousElement->next = newElement;
        }
        numElements++;
        return true;
      }
    }
    return false;
  }

  bool popMinElementSortedListCC(coordinate & coords, uc8 & value) {
    if (first != NULL) {
      coords = first->coordinates;
      value = first->value;
      node_channel_coordinate * tempNode = first;
      first = tempNode->next;
      if (first) {
        first->previous = NULL;
      } else {
        last = first;
      }
      delete tempNode;
      numElements--;
      return true;
    } else {
      return false;
    }
  }
  
  void emptyList() { /* too tricky */
    if ( first) {
      if ( first->next) {
        for(node_channel_coordinate * temp = first->next; temp; temp = temp->next) {
          delete temp->previous;
        }
      }
      delete last;
    }
    first = last = NULL;
  }

  ~list_channel_coordinate() {
    emptyList();
  }

  const ui32 getNumElements() const { return numElements; }
};


//--------------------------

//#undef DEBUG

#endif