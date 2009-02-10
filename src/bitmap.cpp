#include "bitmap.h"

#ifdef DEBUG
  #include <cstdio>
#endif

/////////////////////////////////////////////////////
// Contructors
////////////////////////////////////////////////////

BitmapBase::BitmapBase(const ui32 _width, const ui32 _height)
		: width (_width),
		  height (_height) {}

BitmapBase::BitmapBase(const ui32 _width, const ui32 _height, 
			struct pixel24 * _data)
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
BitmapBase::printBMPDataChunk() const {
  char * fileContent = new char[getDataSize()];
  insBMPDataChunk(getDataSize(),fileContent);
  return fileContent;
}


bool 
BitmapBase::insBMPDataChunk(const ui32 _size,char * _output) const {
  if (_size != getDataSize()) {
    return false;
  }
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
      printf("Blu: %d ",_output[h++] = (((dataMatrix + width * i + j)->blue) & MASK));
      printf("Verde: %d ",_output[h++] = (((dataMatrix + width * i + j)->green) & MASK));
      printf("Rosso: %d \n",_output[h++] = (((dataMatrix + width * i + j)->red) & MASK));
#else
      _output[h++] = (((dataMatrix + width * i + j)->blue) & MASK);
      _output[h++] = (((dataMatrix + width * i + j)->green) & MASK);
      _output[h++] = (((dataMatrix + width * i + j)->red) & MASK);
#endif
    }
#ifdef DEBUG
    printf("Posizionamento padding\n\n");
#endif
    for (j = 0; j < numPadding; j++) {
      _output[h++] = 0x00;
    }
  }
#ifdef DEBUG
  printf("La stringa è: ");
  for (i = 0; i < h; i++) {
    printf("%d ",_output[i]);
  }
  printf("\n\n");
#endif
  return true;
}
