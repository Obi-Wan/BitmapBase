#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "bitmap_types.h"

class transformations {
public:
  static void gradient(struct size _size, struct pixel24 * matrix);
  static void inverseGradient(struct size _size, struct pixel24 * matrix);
  static void sinAndGradient(struct size _size, struct pixel24 * matrix);
  static void sinAllChannels(struct size _size, struct pixel24 * matrix);
  static void transpose(struct size _size, struct pixel24 * matrix);

  static void saturation(struct size _size, struct pixel24 * matrix);
  static void decolorify(struct size _size, struct pixel24 * matrix, 
                         const ui32 num);

  /* Maybe in future */
//  static void classicaAdjoint(struct size _size, struct pixel24 * matrix);
//  static void triangularize(struct size _size, struct pixel24 * matrix);
//  static si32_3 determinant(struct size _size,const struct pixel24 * matrix);
};

#endif
