#include "transformations.h"

void 
transformations::gradient(struct size _size,struct pixel24 * matrix) {
  ui32 i = 0, j = 0;
  for(i = 0; i < _size.height; i++) {
    for(j = 0; j < _size.width; j++) {
      (matrix + i * _size.width + j)->red = i * 255 / _size.height;
      (matrix + i * _size.width + j)->blue = j * 255 / _size.width;
      (matrix + i * _size.width + j)->green = i * 255 / _size.width;
    }
  }
}

void 
transformations::inverseGradient(struct size _size,struct pixel24 * matrix) {
  ui32 i = 0, j = 0;
  for(i = 0; i < _size.height; i++) {
    for(j = 0; j < _size.width; j++) {
      (matrix + i * _size.width + j)->red = (_size.height - i) * 255 / _size.height;
      (matrix + i * _size.width + j)->blue = j * 255 / _size.width;
      (matrix + i * _size.width + j)->green = i * 255 / _size.width;
    }
  }
}

