#include "bitmap_file.h"

#ifdef DEBUG
  #include <cstdio>
#endif

#define INFO_FILE_HEADER_SIZE 18
#define STATIC_PROPS_HEADER_SIZE 28
#define STATIC_PROPS_HEADER_OFFSET (INFO_FILE_HEADER_SIZE + 8)

static const char INFO_FILE_HEADER[INFO_FILE_HEADER_SIZE] = { 
		0x42, 0x4d, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,
		0x00, 0x00
		};

static const char STATIC_PROPS_HEADER[STATIC_PROPS_HEADER_SIZE] = { 
		0x01, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x10, 0x00, 0x00, 0x00, 0x13, 0x0b, 0x00, 0x00,
		0x13, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00
		};

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

char * 
BitmapFile::printBMPFile() {
  ui32 i = 0;
  const ui32 dataSize = getDataSize();
  const ui32 fileSize = getFileSize();
  char * fileContent = new char[fileSize];
  for(i = 0; i < INFO_FILE_HEADER_SIZE;i++) {
    fileContent[i] = INFO_FILE_HEADER[i];
  }
  putNumberEndianessAware(getWidth(),4, (fileContent + 18) );
  putNumberEndianessAware(getHeight(),4, (fileContent + 22) );
  for(i = 0; i < STATIC_PROPS_HEADER_SIZE;i++) {
    fileContent[STATIC_PROPS_HEADER_OFFSET + i] = STATIC_PROPS_HEADER[i];
  }
  insBMPDataChunk(getDataSize(),&fileContent[HEADER_SIZE]);
#ifdef DEBUG
  printf("\nIl file è: ");
  for (i = 0; i < fileSize; i++) {
    printf("%d ",fileContent[i]);
  }
  printf("\n");
#endif
  return fileContent;
}

inline void 
BitmapFile::putNumberEndianessAware(const ui32 _num, const ui32 _size, char * _output)
{
  int i = 0;
  for (i = 0; i < _size; i++) {
    _output[i] = ((_num >> (i*8)) & MASK);
  }
}
