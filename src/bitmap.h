#ifndef BITMAP_H
#define BITMAP_H

#define HEADER_SIZE 54	// meant in Byte
#define PIXEL_SIZE 1	// meant in Byte

#include "bitmap_types.h"

// No data coherence granted.

class BitmapBase {
  pixel24 * dataMatrix;

  ui32 width;
  ui32 height;
public:
  BitmapBase(const ui32 _width, const ui32 _height);
  BitmapBase(const ui32 _width, const ui32 _height, pixel24 * _data);

  void setSize(const size _size) {
    width = _size.width;
    height = _size.height;
  }
  bool readDataMatrix(const sc8 * _data);
  void setDataMatrix(pixel24 * _data);
  pixel24 * getDataMatrix(void) { return dataMatrix; }

  char * printBMPDataChunk() const;
  bool insBMPDataChunk(const ui32 _size,char * _output) const;

  ui32 getWidth(void) const { return width; }
  ui32 getHeight(void) const { return height; }
  ui32 getDataSize(void) const {
    return (PIXEL_SIZE * getWidth() * getHeight()) * 3 + 
  		(getWidth() % 4) * getHeight();
  } // in byte
};

#endif
