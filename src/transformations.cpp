#include "transformations.h"

#include "bitmap_utils.h"
#include "bitmap_funcs.h"
#include <cmath>
#define PI 3.14159265

void 
transformations::gradient(size _size, pixel24 * matrix) {
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
transformations::inverseGradient(size _size, pixel24 * matrix) {
  ui32 i = 0, j = 0;
  for(i = 0; i < _size.height; i++) {
    for(j = 0; j < _size.width; j++) {
      (matrix + i * _size.width + j)->red =
              (_size.height - i) * 255 / _size.height;
      (matrix + i * _size.width + j)->blue =
              j * 255 / _size.width;
      (matrix + i * _size.width + j)->green =
              i * 255 / _size.width;
    }
  }
}

void 
transformations::sinAllChannels(size _size, pixel24 * matrix) {
  ui32 i = 0, j = 0;
  for(i = 0; i < _size.height; i++) {
    for(j = 0; j < _size.width; j++) {
      (matrix + i * _size.width + j)->red =
              128 + 127 * ( - sin( - i * 4 * PI / _size.height ));
      (matrix + i * _size.width + j)->blue =
              128 + 127 * ( - sin( - j * 4 * PI / _size.width ));
      (matrix + i * _size.width + j)->green = 
              128 + 127 * ( - sin( ( (i * 4 * PI / _size.height) +
                                     (j * 4 * PI / _size.width) ) / 2 ));
    }
  }
}


void 
transformations::sinAndGradient(size _size,pixel24 * matrix) {
  ui32 i = 0, j = 0;
  for(i = 0; i < _size.height; i++) {
    for(j = 0; j < _size.width; j++) {
      (matrix + i * _size.width + j)->red =
              128 + 127 * ( - sin( - i * 4 * PI / _size.height ));
      (matrix + i * _size.width + j)->blue =
              128 + 127 * ( - sin( - j * 4 * PI / _size.width ));
      (matrix + i * _size.width + j)->green = 
              128 + 127 * ( - sin( ( (i * 4 * PI / _size.height) +
                                     (j * 4 * PI / _size.width) ) / 2 ));
    }
  }
}

void
transformations::transpose(size _size, pixel24 * matrix) {
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

void
transformations::decolorify(size _size, pixel24 * matrix,
                            const ui32 num)
{
  ui32 i = 0, j = 0;
  const ui32 baseStep = 255 / num;
  uc8 temp = 0;
  for (i = 0; i < _size.height; i++) {
    for (j = 0; j < _size.width; j++) {
      temp = (matrix + i * _size.width + j)->red;
      (matrix + i * _size.width + j)->red = temp - ( temp % baseStep);
      temp = (matrix + i * _size.width + j)->green;
      (matrix + i * _size.width + j)->green = temp - ( temp % baseStep);
      temp = (matrix + i * _size.width + j)->blue;
      (matrix + i * _size.width + j)->blue = temp - ( temp % baseStep);
    }
  }
}

void
transformations::saturation(size _size, pixel24* matrix) {
  ui32 i = 0, j = 0;
  ordered_list_channel_coordinate 
          * listRed = createOrderedListCC(),
          * listGreen = createOrderedListCC(), 
          * listBlue = createOrderedListCC();
  for (i = 0; i < _size.height; i++) { /* ciclo sulla y */
    for (j = 0; j < _size.width; j++) { /* ciclo sulla x */
      if ((matrix + i * _size.width + j)->red > 192) {
        addElementOrderedListCC(*listRed,coordinate(j,i),
                                (matrix + i * _size.width + j)->red);
      }
      if ((matrix + i * _size.width + j)->green > 192) {
        addElementOrderedListCC(*listGreen,coordinate(j,i),
                                (matrix + i * _size.width + j)->green);
      }
      if ((matrix + i * _size.width + j)->blue > 192) {
        addElementOrderedListCC(*listBlue,coordinate(j,i),
                                (matrix + i * _size.width + j)->blue);
      }
    }
  }

  /* i vettori vanno ordinati in ordine crescente, per non processare in modo
   * diverso i vari punti */

  saturatelistOfPoints(_size,matrix,listRed,COLOR_RED);
  saturatelistOfPoints(_size,matrix,listGreen,COLOR_GREEN);
  saturatelistOfPoints(_size,matrix,listBlue,COLOR_BLUE);
  
}

inline void
transformations::saturatelistOfPoints(const size& _size,
                                      pixel24* matrix,
                                      ordered_list_channel_coordinate* list,
                                      const ui32& color) {
  uc8 ref = 0, tempElabRef = 0;
  coordinate coords(0,0);
  pixel24 * tempRefToPoint = NULL;
  rel_coordinate upperMaxCoords(0,0),lowerMaxCoords(0,0);

  for (;isEmptyOrderedListCC(*list);) {

    popMinElementOrderedListCC(*list,coords,ref);

    upperMaxCoords = rel_coordinate(max(-10,-coords.x),max(-10,-coords.y));
    lowerMaxCoords = rel_coordinate(min(10,_size.width  - coords.x),
                                    min(10,_size.height - coords.y));

    for(si32 contX = upperMaxCoords.x; contX < lowerMaxCoords.x; contX++) {
      for(si32 contY = upperMaxCoords.y; contY < lowerMaxCoords.y; contY++) {

        tempRefToPoint = getPointerRelCoords(matrix,_size,coords,
                                             rel_coordinate(contX,contY));
        if (tempRefToPoint->getChannel(color) < ref) {
          tempElabRef = tempRefToPoint->getChannel(color) +
                  ( (ref - tempRefToPoint->getChannel(color)) /
                    ( 2 * distance( rel_coordinate(contX,contY) ) ) );
          tempRefToPoint->getChannel(color) = absMin(255, tempElabRef);
        }
      }
    }
  } /* Fine ciclo sugli elementi della lsita */
}

