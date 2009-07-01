#include "transformations.h"

#include "bitmap_utils.h"
#include "bitmap_funcs.h"
#include <cmath>
#define PI 3.14159265

#define DEBUG

#ifdef DEBUG
    #include <stdio.h>
#endif

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
transformations::saturation(size _size, pixel24* matrix, uc8 threshold) {
  ui32 i = 0, j = 0;
  list_channel_coordinate
          * listRed = list_channel_coordinate::createListCC(),
          * listGreen = list_channel_coordinate::createListCC(),
          * listBlue = list_channel_coordinate::createListCC();
  for (i = 0; i < _size.height; i++) { /* ciclo sulla y */
    for (j = 0; j < _size.width; j++) { /* ciclo sulla x */
      if ((matrix + i * _size.width + j)->red > threshold) {
        listRed->addSortedElementListCC(coordinate(j,i),
                                (matrix + i * _size.width + j)->red);
      }
      if ((matrix + i * _size.width + j)->green > threshold) {
        listGreen->addSortedElementListCC(coordinate(j,i),
                                (matrix + i * _size.width + j)->green);
      }
      if ((matrix + i * _size.width + j)->blue > threshold) {
        listBlue->addSortedElementListCC(coordinate(j,i),
                                (matrix + i * _size.width + j)->blue);
      }
    }
  }

#ifdef DEBUG
  printf("scan iniziale finito. Elementi da processare:\n "
          "rossi: %d , verdi: %d , blu: %d = totali: %d\n",
         listRed->getNumElements(),
         listGreen->getNumElements(),
         listBlue->getNumElements(),
           listBlue->getNumElements() + listGreen->getNumElements() +
           listRed->getNumElements()
         );
#endif

  /* i vettori vanno ordinati in ordine crescente, per non processare in modo
   * diverso i vari punti */

  saturatelistOfPoints(_size,matrix,listRed,COLOR_RED);
#ifdef DEBUG
  printf("Processamento rossi finito\n");
#endif
  saturatelistOfPoints(_size,matrix,listGreen,COLOR_GREEN);
#ifdef DEBUG
  printf("Processamento verdi finito\n");
#endif
  saturatelistOfPoints(_size,matrix,listBlue,COLOR_BLUE);
#ifdef DEBUG
  printf("Processamento blu finito\n");
#endif
  
}

inline void
transformations::saturatelistOfPoints(const size& _size,
                                      pixel24* matrix,
                                      list_channel_coordinate* list,
                                      const ui32& color) {
  uc8 ref = 0;
  ui32 tempElabRef = 0;
  coordinate coords(0,0);
  pixel24 * tempRefToPoint = NULL;
  rel_coordinate upperMaxCoords(0,0),lowerMaxCoords(0,0);

  for (;!list->isEmptyListCC();) {

    list->popMinElementSortedListCC(coords,ref);

    upperMaxCoords = rel_coordinate(max(-20,-coords.x),max(-20,-coords.y));
    lowerMaxCoords = rel_coordinate(min(20,_size.width  - coords.x),
                                    min(20,_size.height - coords.y));

    for(si32 contX = upperMaxCoords.x; contX < lowerMaxCoords.x; contX++) {
      for(si32 contY = upperMaxCoords.y; contY < lowerMaxCoords.y; contY++) {

        tempRefToPoint = getPointerRelCoords(matrix,_size,coords,
                                             rel_coordinate(contX,contY));
        if (tempRefToPoint->getChannel(color) < ref) {
#ifdef DEBUG
       //   printf("il punto di coordinate (%d,%d) verrà aumentato\n",coords.x + contX,
     //            coords.y + contY);
#endif
          tempElabRef = tempRefToPoint->getChannel(color) +
                  ( (ref - tempRefToPoint->getChannel(color)) /
                    ( distanceQuad( rel_coordinate(contX,contY) ) ) );
          tempRefToPoint->getChannel(color) = absMin(255, tempElabRef);
        }
      }
    }
#ifdef DEBUG
//    printf("punto di coordinate (%d,%d) saturato con successo\n",coords.x,
  //         coords.y);
    //printf("ne rimangono: %d\n",list->numElements);
#endif
  } /* Fine ciclo sugli elementi della lsita */
}

#undef DEBUG
