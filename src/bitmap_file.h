#ifndef BITMAP_FILE_H
#define BITMAP_FILE_H

#include "bitmap.h"

class BitmapFile : protected BitmapBase {
  
public:
  BitmapFile(struct size _size);
  BitmapFile(struct size _size, struct pixel24 * _data);

  char * printBMPFile();
  ui32 getFileSize(); // in byte
  ui32 getDataSize(); // in byte
};

#endif
