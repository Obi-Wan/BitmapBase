#ifndef BITMAP_FILE_H
#define BITMAP_FILE_H

#include "bitmap.h"

class BitmapFile : protected BitmapBase {
public:
  BitmapFile(struct size _size);
  BitmapFile(struct size _size, struct pixel24 * _data);

  char * printBMPFile(void);
  bool readBMPFile(const ui32 _size, const char *); 

  ui32 getFileSize(void){
    return (HEADER_SIZE + getDataSize());
  } // in byte
};

#endif
