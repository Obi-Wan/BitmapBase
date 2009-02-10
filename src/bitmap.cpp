#include "bitmap.h"

#ifdef DEBUG
  #include <cstdio>
#endif

/////////////////////////////////////////////////////
// Contructors
////////////////////////////////////////////////////

BitmapBase::BitmapBase(ui32 _width, ui32 _height)
		: width (_width),
		  height (_height) {}

BitmapBase::BitmapBase(ui32 _width, ui32 _height, struct pixel24 * _data)
		: width (_width),
		  height (_height),
		  dataMatrix (_data) {}


/////////////////////////////////////////////////////
// Other Functions
////////////////////////////////////////////////////

inline void 
BitmapBase::setDataMatrix (struct pixel24 * _data) {
  if (dataMatrix) {
    delete dataMatrix;
  }
  dataMatrix = _data;
}

char * 
BitmapBase::printBMPDataChunk() {
  char * fileContent = new char[PIXEL_SIZE * width * height + 1];
  ui16 numPadding = (width % 4);
#ifdef DEBUG
  printf("Padding: %d\n",numPadding);
#endif
  ui32 i = 0, j = 0, h = 0;
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
#ifdef DEBUG
      printf("Pixel ( %d , %d )\n",j,i);
      printf("Posizione %d \n",j + i * width);
      printf("Blu: %d ",fileContent[h++] = (((dataMatrix + width * i + j)->blue) & MASK));
      printf("Verde: %d ",fileContent[h++] = (((dataMatrix + width * i + j)->green) & MASK));
      printf("Rosso: %d \n",fileContent[h++] = (((dataMatrix + width * i + j)->red) & MASK));
#else
      fileContent[h++] = (((dataMatrix + width * i + j)->blue) & MASK);
      fileContent[h++] = (((dataMatrix + width * i + j)->green) & MASK);
      fileContent[h++] = (((dataMatrix + width * i + j)->red) & MASK);
#endif
    }
#ifdef DEBUG
    printf("Posizionamento padding\n\n");
#endif
    for (j = 0; j < numPadding; j++) {
      fileContent[h++] = 0x00;
    }
  }
  fileContent[h] = '\0';
#ifdef DEBUG
  printf("La stringa è: ");
  for (i = 0; i < h; i++) {
    printf("%d ",fileContent[i]);
  }
  printf("\n\n");
#endif
  return fileContent;
}

inline void 
BitmapBase::setSize(struct size _size) {
  width = _size.width;
  height = _size.height;
}
