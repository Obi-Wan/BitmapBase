#include "bitmap_file.h"
#include "transformations.h"
#include "DiskIO.h"
#include <cstdio>

int main(si32 argc, sc8 **argv) {
  const size newSize = {500 , 500};
  struct pixel24 * the_matrix = new pixel24[newSize.width * newSize.height + 1];
  transformations::inverseGradient(newSize,the_matrix);
  BitmapFile theBitmap(newSize,the_matrix);
/*  FILE * fileOut = fopen("prova.bmp","w");
  if (fileOut != NULL) {
    fwrite(theBitmap.printBMPFile(),sizeof(char),theBitmap.getFileSize(),
    		fileOut);
  }*/
  DiskIO * writer = DiskIO::createFileSocket(WRITE,(const sc8 *)"prova.bmp",&theBitmap);
  writer->write();
  return 0;
}
