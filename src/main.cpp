#include "bitmap_file.h"
#include "transformations.h"
#include <cstdio>

int main(si32 argc, si32 **argv) {
  const size newSize = {500 , 500};
  struct pixel24 * the_matrix = new pixel24[newSize.width * newSize.height + 1];
  transformations::inverseGradient(newSize,the_matrix);
  BitmapFile theBitmap(newSize,the_matrix);
  FILE * fileOut = fopen("prova.bmp","w");
  if (fileOut != NULL) {
    fwrite(theBitmap.printBMPFile(),sizeof(char),theBitmap.getFileSize(),
    		fileOut);
  }
  return 0;
}
