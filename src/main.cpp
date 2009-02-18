#include "bitmap_file.h"
#include "transformations.h"
#include <cstdio>

int main() {
  const size newSize = {512 , 512};
  struct pixel24 * the_matrix = new pixel24[newSize.width * newSize.height + 1];
  transformations::sinAndGradient(newSize,the_matrix);
  //transformations::transpose(newSize,the_matrix);
  //transformations::inverseGradient(newSize,the_matrix);
  BitmapFile theBitmap(newSize,the_matrix);
  FILE * fileOut = fopen("prova.bmp","w");
  if (fileOut != NULL) {
    fwrite(theBitmap.printBMPFile(),sizeof(char),theBitmap.getFileSize(),
    		fileOut);
  }
  return 0;
}
