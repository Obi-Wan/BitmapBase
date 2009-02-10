#include "bitmap_file.h"

#ifdef DEBUG
  #include <cstdio>
#endif

/////////////////////////////////////////////////////
// Contructors
////////////////////////////////////////////////////

BitmapFile::BitmapFile(struct size _size)
		: BitmapBase(_size.width,_size.height) {}

BitmapFile::BitmapFile(struct size _size, struct pixel24 * _data)
		: BitmapBase(_size.width,_size.height,_data) {}


/////////////////////////////////////////////////////
// Other Functions
////////////////////////////////////////////////////

// potential bug with width/height > 255

char * 
BitmapFile::printBMPFile() {
  ui32 i = 0;
  const ui32 dataSize = getDataSize();
  const ui32 fileSize = getFileSize();
  char * fileContent = new char[fileSize];
  char * dataChunk = printBMPDataChunk();
#ifdef DEBUG
  printf("The size is: %d\nIl data-chunk è: ",dataSize);
#endif
  for (i = 0; i < dataSize; i++) {
#ifdef DEBUG
    printf("%d ",fileContent[HEADER_SIZE + i] = dataChunk[i]);
#else
    fileContent[HEADER_SIZE + i] = dataChunk[i];
#endif
  }
  //delete []dataChunk;
  fileContent[0] = 0x42;
  fileContent[1] = 0x4d;
  fileContent[2] = 0x46;
  fileContent[3] = fileContent[4] = fileContent[5] = 0x00;
  fileContent[6] = fileContent[7] = 0x00;
  fileContent[8] = fileContent[9] = 0x00;
  fileContent[10] = 0x36;
  fileContent[11] = fileContent[12] = fileContent[13] = 0x00;
  fileContent[14] = 0x28;
  fileContent[15] = fileContent[16] = fileContent[17] = 0x00;
  fileContent[18] = getWidth();
  fileContent[19] = fileContent[20] = fileContent[21] = 0x00;
  fileContent[22] = getHeight();
  fileContent[23] = fileContent[24] = fileContent[25] = 0x00;
  fileContent[26] = 0x01;
  fileContent[27] = 0x00;
  fileContent[28] = 0x18;
  fileContent[29] = 0x00;
  fileContent[30] = fileContent[31] = fileContent[32] = fileContent[33] = 0x00;
  fileContent[34] = 0x10;
  fileContent[35] = fileContent[36] = fileContent[37] = 0x00;
  fileContent[38] = 0x13;
  fileContent[39] = 0x0b;
  fileContent[40] = fileContent[41] = 0x00;
  fileContent[42] = 0x13;
  fileContent[43] = 0x0b;
  fileContent[44] = fileContent[45] = 0x00;
  fileContent[46] = fileContent[47] = fileContent[48] = fileContent[49] = 0x00;
  fileContent[50] = fileContent[51] = fileContent[52] = fileContent[53] = 0x00;
#ifdef DEBUG
  printf("\nIl file è: ");
  for (i = 0; i < fileSize; i++) {
    printf("%d ",fileContent[i]);
  }
  printf("\n");
#endif
  return fileContent;
}

ui32
BitmapFile::getFileSize() {
  return (HEADER_SIZE + getDataSize());
}

ui32
BitmapFile::getDataSize() {
  return (PIXEL_SIZE * getWidth() * getHeight()) * 3 + 
  		(getWidth() % 4) * getHeight();
}

