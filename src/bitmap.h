#ifndef BITMAP_H
#define BITMAP_H

#define HEADER_SIZE 54	// meant in Byte
#define PIXEL_SIZE 1	// meant in Byte

#include "bitmap_types.h"

// No data coherence granted.

class BitmapBase {
  struct pixel24 * dataMatrix;

  ui32 width;
  ui32 height;
public:
  BitmapBase(const ui32 _width, const ui32 _height);
  BitmapBase(const ui32 _width, const ui32 _height, struct pixel24 * _data);

  void setSize(const struct size _size) {
    width = _size.width;
    height = _size.height;
  }
  bool readDataMatrix(const sc8 * _data);
  void setDataMatrix(struct pixel24 * _data);
  struct pixel24 * getDataMatrix(void) { return dataMatrix; }

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
