#include "bitmap_file.h"
#include "transformations.h"
#include <cstdio>

int main() {
//  sc8 MagicNumber[2] = { 0 , 0 };
//  sscanf("42 4d","%x %x",&MagicNumber[0],&MagicNumber[1]);
//  printf("%x %x\n",MagicNumber[0],MagicNumber[1]);
  const size newSize = {128 , 128};
  struct pixel24 * the_matrix = new pixel24[newSize.width * newSize.height + 1];
/*  const size newSize = { 2 , 2 };
  struct pixel24 * the_matrix = new pixel24[newSize.width * newSize.height];
  the_matrix[0].blue = 0;
  the_matrix[0].green = 0;
  the_matrix[0].red = 0xff;
  the_matrix[1].blue = 0xff;
  the_matrix[1].green = 0xff;
  the_matrix[1].red = 0xff;
  the_matrix[2].blue = 0xff;
  the_matrix[2].green = 0;
  the_matrix[2].red = 0;
  the_matrix[3].blue = 0;
  the_matrix[3].green = 0xff;
  the_matrix[3].red = 0;*/
  transformations::inverseGradient(newSize,the_matrix);
  BitmapFile theBitmap(newSize,the_matrix);
  FILE * fileOut = fopen("prova.bmp","w");
  if (fileOut != NULL) {
    fwrite(theBitmap.printBMPFile(),sizeof(char),theBitmap.getFileSize(),
    		fileOut);
  }
  return 0;
}
