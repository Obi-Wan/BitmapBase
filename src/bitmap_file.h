#ifndef BITMAP_FILE_H
#define BITMAP_FILE_H

#include "bitmap.h"

class BitmapFile : protected BitmapBase {
  void putNumberEndianessAware(const ui32 _num, const ui32 _size, char * _output);
public:
  BitmapFile(struct size _size);
  BitmapFile(struct size _size, struct pixel24 * _data);

  char * printBMPFile(void);
  ui32 getFileSize(void){
    return (HEADER_SIZE + getDataSize());
  } // in byte
};

#endif
