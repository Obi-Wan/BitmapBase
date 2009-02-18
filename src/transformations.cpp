#include "transformations.h"

#include <cmath>
#define PI 3.14159265

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

void 
transformations::sinAllChannels(struct size _size,struct pixel24 * matrix) {
  ui32 i = 0, j = 0;
  for(i = 0; i < _size.height; i++) {
    for(j = 0; j < _size.width; j++) {
      (matrix + i * _size.width + j)->red = 128 + 127 * ( - sin( - i * 4 * PI / _size.height ));
      (matrix + i * _size.width + j)->blue = 128 + 127 * ( - sin( - j * 4 * PI / _size.width ));
      (matrix + i * _size.width + j)->green = 128 + 127 * ( - sin( ( (i * 4 * PI / _size.height) + (j * 4 * PI / _size.width) ) / 2 ));
    }
  }
}


void 
transformations::sinAndGradient(struct size _size,struct pixel24 * matrix) {
  ui32 i = 0, j = 0;
  for(i = 0; i < _size.height; i++) {
    for(j = 0; j < _size.width; j++) {
      (matrix + i * _size.width + j)->red = 128 + 127 * ( - sin( - i * 4 * PI / _size.height ));
      (matrix + i * _size.width + j)->blue = 128 + 127 * ( - sin( - j * 4 * PI / _size.width ));
      (matrix + i * _size.width + j)->green = 128 + 127 * ( - sin( ( (i * 4 * PI / _size.height) + (j * 4 * PI / _size.width) ) / 2 ));
    }
  }
}

void 
transformations::transpose(struct size _size, struct pixel24 * matrix) {
  ui32 i = 0, j = 0;
  uc8 temp = 0;
  for (i = 0; i < _size.height; i++) {
    for (j = i + 1; j < _size.width; j++) {
      temp = (matrix + i * _size.width + j)->red;
      (matrix + i * _size.width + j)->red = (matrix + j * _size.width + i)->red;
      (matrix + j * _size.width + i)->red = temp;
      temp = (matrix + i * _size.width + j)->green;
      (matrix + i * _size.width + j)->green = (matrix + j * _size.width + i)->green;
      (matrix + j * _size.width + i)->green = temp;
      temp = (matrix + i * _size.width + j)->blue;
      (matrix + i * _size.width + j)->blue = (matrix + j * _size.width + i)->blue;
      (matrix + j * _size.width + i)->blue = temp;
    }
  }
}
