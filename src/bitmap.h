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
  BitmapBase(ui32 _width, ui32 _height);
  BitmapBase(ui32 _width, ui32 _height, struct pixel24 * _data);

  void setSize(struct size _size);
  void setDataMatrix(struct pixel24 * _data);

  char * printBMPDataChunk();

  ui32 getWidth() { return width; }
  ui32 getHeight() { return height; }
};

#endif
