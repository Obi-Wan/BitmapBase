#include "transformations.h"

#include "bitmap_utils.h"
#include "bitmap_funcs.h"
#include <cmath>
#define PI 3.14159265

#define INFO

#if defined( INFO ) || defined( DEBUG )
    #include <stdio.h>
#endif

void 
Transformations::gradient(size _size, pixel24 * matrix) {
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
Transformations::inverseGradient(size _size, pixel24 * matrix) {
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
Transformations::sinAllChannels(size _size, pixel24 * matrix) {
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
Transformations::sinAndGradient(size _size,pixel24 * matrix) {
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
Transformations::transpose(size _size, pixel24 * matrix) {
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
Transformations::decolorify(size _size, pixel24 * matrix,
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

/** This method saturates point near already-saturated points.
 *
 * It considers just the most saturated:
 *
 * 192/256 = 75     %
 * 208/256 = 81.25  %
 * 224/256 = 87.5   %
 * 240/256 = 93.75  %
 */
void
Transformations::saturation(size _size, pixel24* matrix, uc8 threshold) {
  ui32 i = 0, j = 0;
  listChannelCoordinates listRed, listGreen, listBlue;

#ifdef INFO
  printf("Scan iniziale... ");
#endif
  for (i = 0; i < _size.height; i++) { /* ciclo sulla y */
    for (j = 0; j < _size.width; j++) { /* ciclo sulla x */
      if ((matrix + i * _size.width + j)->red > threshold) {
        listRed.addUnsortedElement(coordinate(j,i),
                                (matrix + i * _size.width + j)->red);
      }
      if ((matrix + i * _size.width + j)->green > threshold) {
        listGreen.addUnsortedElement(coordinate(j,i),
                                (matrix + i * _size.width + j)->green);
      }
      if ((matrix + i * _size.width + j)->blue > threshold) {
        listBlue.addUnsortedElement(coordinate(j,i),
                                (matrix + i * _size.width + j)->blue);
      }
    }
  }

#ifdef INFO
  printf("finito!\nElementi da ordinare e processare:\n "
          "rossi: %d , verdi: %d , blu: %d = totali: %d\nOrdinamento... ",
         listRed.getNumElements(),
         listGreen.getNumElements(),
         listBlue.getNumElements(),
           listBlue.getNumElements() + listGreen.getNumElements() +
           listRed.getNumElements()
         );
#endif

  listRed.sortList();
  listGreen.sortList();
  listBlue.sortList();

#ifdef INFO
  printf("ordinati!\n");
#endif

  /* i vettori sono stati ordinati in ordine crescente, per non processare in
   * condizioni diverse i vari punti */

#ifdef INFO
  printf("Processamento rossi... ");
#endif
  saturatelistOfPoints(_size,matrix,listRed,COLOR_RED);
#ifdef INFO
  printf("finito!\nProcessamento verdi... ");
#endif
  saturatelistOfPoints(_size,matrix,listGreen,COLOR_GREEN);
#ifdef INFO
  printf("finito!\nProcessamento blu... ");
#endif
  saturatelistOfPoints(_size,matrix,listBlue,COLOR_BLUE);
#ifdef INFO
  printf("finito!\n");
#endif
}

inline void
Transformations::saturatelistOfPoints(const size& _size,
                                      pixel24* matrix,
                                      listChannelCoordinates & list,
                                      const ui32& color) {
  uc8 ref = 0;
  ui32 tempElabRef = 0;
  coordinate coords(0,0);
  pixel24 * tempRefToPoint = NULL;
  rel_coordinate upperMaxCoords(0,0),lowerMaxCoords(0,0);

  for (;!list.isEmpty();) {

    list.popMinElementSorted(coords,ref);

    upperMaxCoords = rel_coordinate(max(-20,-coords.x),max(-20,-coords.y));
    lowerMaxCoords = rel_coordinate(min(20,_size.width  - coords.x),
                                    min(20,_size.height - coords.y));

    for(si32 contX = upperMaxCoords.x; contX < lowerMaxCoords.x; contX++) {
      for(si32 contY = upperMaxCoords.y; contY < lowerMaxCoords.y; contY++) {

        tempRefToPoint = getPointerRelCoords(matrix,_size,coords,
                                             rel_coordinate(contX,contY));
        if (tempRefToPoint->getChannel(color) < ref) {
          tempElabRef = tempRefToPoint->getChannel(color) +
                  ( (ref - tempRefToPoint->getChannel(color)) /
                    ( distanceQuad( rel_coordinate(contX,contY) ) ) );
          tempRefToPoint->getChannel(color) = absMin(255, tempElabRef);
        }
      }
    }
  } /* Fine ciclo sugli elementi della lsita */
}

#undef INFO
