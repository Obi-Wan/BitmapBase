#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "bitmap_types.h"

class transformations {
public:
  static void gradient(struct size _size, struct pixel24 * matrix);
  static void inverseGradient(struct size _size, struct pixel24 * matrix);
};

#endif
