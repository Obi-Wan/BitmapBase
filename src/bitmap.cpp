#include <stdlib.h>

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
BitmapBase::applyTransform(const Cfg & cfg) {
  
  size _size = {getWidth(),getHeight()};
  ui32 threshold = atoi(cfg.getSubOption(THRESHOLD).c_str());
  ui32 col = atoi(cfg.getSubOption(COLORS).c_str());

  switch (cfg.getTrasform()) {
    case GRADIENT:
      Transformations::gradient(_size,getDataMatrix());
      break;
    case INVERSE_GRADIENT:
      Transformations::inverseGradient(_size,getDataMatrix());
      break;
    case SIN_AND_GRADIENT:
      Transformations::sinAndGradient(_size,getDataMatrix());
      break;
    case SIN_ALL_CHANNELS:
      Transformations::sinAllChannels(_size,getDataMatrix());
      break;
    case TRANSPOSE:
      Transformations::transpose(_size,getDataMatrix());
      break;
    case SATURATION:
      //Transformations::saturation(_size,getDataMatrix(),192);
      Transformations::saturation(_size,getDataMatrix(),threshold);
      break;
    case DECOLORIFY:
      Transformations::decolorify(_size,getDataMatrix(),col);
      break;
    case SIN_VERT_WAVE:
      Transformations::sin_vert_wave(_size,getDataMatrix());
      break;
  }


}
