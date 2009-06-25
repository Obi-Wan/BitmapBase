#include "bitmap.h"

#ifdef DEBUG
  #include <cstdio>
#endif

#include "transformations.h"

/////////////////////////////////////////////////////
// Contructors
////////////////////////////////////////////////////

BitmapBase::BitmapBase(const ui32 _width, const ui32 _height)
		: width (_width),
		  height (_height),
          dataMatrix (NULL) {}

BitmapBase::BitmapBase(const ui32 _width, const ui32 _height, pixel24 * _data)
		: width (_width),
		  height (_height),
		  dataMatrix (_data) {}


/////////////////////////////////////////////////////
// Other Functions
////////////////////////////////////////////////////

inline void 
BitmapBase::setDataMatrix (pixel24 * _data) {
  if (dataMatrix) {
    delete dataMatrix;
  }
  dataMatrix = _data;
}

bool 
BitmapBase::emitBMPMatrixDataToWrite(const ui32 _size,char * _output) const {
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
      _output[h++] = (((dataMatrix + width * i + j)->blue) & MASK);
      _output[h++] = (((dataMatrix + width * i + j)->green) & MASK);
      _output[h++] = (((dataMatrix + width * i + j)->red) & MASK);
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

bool 
BitmapBase::readDataMatrix24(const sc8 * _data) { /* I should control size */
  ui16 numPadding = (width % 4);
  ui32 i = 0, j = 0, h = 0;
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      ((dataMatrix + width * i + j)->blue) = _data[h++];
      ((dataMatrix + width * i + j)->green) = _data[h++];
      ((dataMatrix + width * i + j)->red) = _data[h++];
    }
    h += numPadding;
  }
  return true;
}


/////////////////////////////////////////////////////
// Transform Functions
////////////////////////////////////////////////////

void
BitmapBase::applyTransform() {
  
  size _size = {getWidth(),getHeight()};

  //transformations::sinAndGradient(_size,the_matrix);
  //transformations::transpose(_size,the_matrix);
  //transformations::inverseGradient(_size,the_matrix);

  //transformations::transpose(_size,getDataMatrix());
  //transformations::decolorify(_size,the_matrix,16);

  transformations::saturation(_size,getDataMatrix(),224);
  //transformations::saturation(_size,getDataMatrix(),224);
}
