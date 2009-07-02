#ifndef BITMAP_FILE_H
#define BITMAP_FILE_H

#include "bitmap.h"
#include "transformations.h"

class BitmapFile : protected BitmapBase {
public:
  BitmapFile();
  BitmapFile(size _size);
  BitmapFile(size _size, pixel24 * _data);

  char * emitBMPFile(void);
  bool readBMPFile(const ui32 _size, const char *); 

  ui32 getFileSize(void){
    return (HEADER_SIZE + getDataSize());
  } // in byte

  void applyTransform(const Cfg & cfg) {
    BitmapBase::applyTransform(cfg);
  };
};

#endif
