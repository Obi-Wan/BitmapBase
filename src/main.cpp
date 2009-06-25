#include "bitmap_file.h"
#include "transformations.h"
#include "DiskIO.h"
#include <cstdio>

int main(si32 argc, char **argv) {
  
  BitmapFile * theBitmap = new BitmapFile();

  DiskIO * reader = DiskIO::createFileSocket(READ,(const sc8 *)"prova.bmp",theBitmap);
  reader->read();

  theBitmap->applyTransform();

  DiskIO * writer = DiskIO::createFileSocket(WRITE,(const sc8 *)"prova2.bmp",theBitmap);
  writer->write();
  return 0;
}
