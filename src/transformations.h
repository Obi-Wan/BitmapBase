#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "bitmap_types.h"
#include "bitmap_utils.h"

enum TransformType {
  GRADIENT,
  INVERSE_GRADIENT,
  SIN_AND_GRADIENT,
  SIN_ALL_CHANNELS,
  TRANSPOSE,
  SATURATION,
  DECOLORIFY,
  SIN_VERT_WAVE
};

const static char * transfomNames[] = {
  "grad",
  "inv_grad",
  "sin_grad",
  "sin",
  "transp",
  "satur",
  "decolor",
  "sin_vert_wave"
};

class Transformations {
public:
  static void gradient(const size & _size, pixel24 * matrix);
  static void inverseGradient(const size & _size, pixel24 * matrix);
  static void sinAndGradient(const size & _size, pixel24 * matrix);
  static void sinAllChannels(const size & _size, pixel24 * matrix);

  static void transpose(size & _size, pixel24 * matrix);
  static void sin_vert_wave(const size & _size, pixel24 * matrix);

  static void saturation(const size & _size, pixel24 * matrix, uc8 threshold);
  static void decolorify(const size & _size, pixel24 * matrix, const ui32 num);

  /* Maybe in future */
//  static void classicaAdjoint(struct size _size, struct pixel24 * matrix);
//  static void triangularize(struct size _size, struct pixel24 * matrix);
//  static si32_3 determinant(struct size _size,const struct pixel24 * matrix);
  
private:
  inline static void saturatelistOfPoints(const size & _size,
                                   pixel24 * matrix,
                                   listChannelCoordinates & list,
                                   const ui32 & color);
};

#endif
