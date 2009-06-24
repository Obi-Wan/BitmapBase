#include "bitmap_file.h"
#include "bitmap_funcs.h"

#ifdef DEBUG
  #include <cstdio>
#endif

#define TYPE_FILE_HEADER_SIZE 2
static const char TYPE_FILE_HEADER[TYPE_FILE_HEADER_SIZE] = { 
		0x42, 0x4d
		};

#define APPLICATION_SPECIFIC_DATA_SIZE 4
#define APPLICATION_SPECIFIC_DATA_OFFSET 6
static const char APPLICATION_SPECIFIC_DATA[APPLICATION_SPECIFIC_DATA_SIZE] = { 
		0x00, 0x00, 0x00, 0x00
		};

#define OFFSET_OF_DATA_SIZE 4
#define OFFSET_OF_DATA_OFFSET 10
#define HEADER_SIZE 54

#define REMAINING_HEADER_BYTES_SIZE 4
#define REMAINING_HEADER_BYTES_OFFSET 14
#define REMAINING_HEADER_BYTES 40

#define WIDTH_OF_BITMAP_SIZE 4
#define WIDTH_OF_BITMAP_OFFSET 18

#define HEIGHT_OF_BITMAP_SIZE 4
#define HEIGHT_OF_BITMAP_OFFSET 22

#define STATIC_PROPS_HEADER1_SIZE 8
#define STATIC_PROPS_HEADER1_OFFSET 26
static const char STATIC_PROPS_HEADER1[STATIC_PROPS_HEADER1_SIZE] = { 
		0x01, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
		};

#define RAW_DATA_SPECIFICATION_SIZE 4
#define RAW_DATA_SPECIFICATION_OFFSET 34

#define STATIC_PROPS_HEADER2_SIZE 16
#define STATIC_PROPS_HEADER2_OFFSET 38
static const char STATIC_PROPS_HEADER2[STATIC_PROPS_HEADER2_SIZE] = { 
		0x13, 0x0b, 0x00, 0x00, 0x13, 0x0b, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		};

/////////////////////////////////////////////////////
// Contructors
////////////////////////////////////////////////////

BitmapFile::BitmapFile(size _size)
		: BitmapBase(_size.width,_size.height) {}

BitmapFile::BitmapFile(size _size, pixel24 * _data)
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
  putStringTo2bytesEndianessAware(TYPE_FILE_HEADER,fileContent);
  putNumTo4bytesEndianessAware(fileSize,fileContent+2);
  putStringEndianessAware(APPLICATION_SPECIFIC_DATA,
		  APPLICATION_SPECIFIC_DATA_SIZE,
		  fileContent+APPLICATION_SPECIFIC_DATA_OFFSET);
  putNumTo4bytesEndianessAware(HEADER_SIZE,
		  fileContent+OFFSET_OF_DATA_OFFSET);
  putNumTo4bytesEndianessAware(REMAINING_HEADER_BYTES,
		  fileContent+REMAINING_HEADER_BYTES_OFFSET);
  putNumTo4bytesEndianessAware(getWidth(),fileContent+WIDTH_OF_BITMAP_OFFSET);
  putNumTo4bytesEndianessAware(getHeight(),fileContent+HEIGHT_OF_BITMAP_OFFSET);
  putStringEndianessAware(STATIC_PROPS_HEADER1,
		  STATIC_PROPS_HEADER1_SIZE,
		  fileContent+STATIC_PROPS_HEADER1_OFFSET);
  putNumTo4bytesEndianessAware(dataSize,
		  fileContent+RAW_DATA_SPECIFICATION_OFFSET);
  putStringEndianessAware(STATIC_PROPS_HEADER2,
		  STATIC_PROPS_HEADER2_SIZE,
		  fileContent+STATIC_PROPS_HEADER2_OFFSET);
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

bool
BitmapFile::readBMPFile(const ui32 _size,const char * fileContent) {
  const ui32 data_offset = getNumBy4bytesEndianessAware(fileContent+10);
  const size pictureSize = { 
  		getNumBy4bytesEndianessAware(fileContent+18), 
		getNumBy4bytesEndianessAware(fileContent+22)
		};
  const ui16 bitsPerPixel = getNumBy2bytesEndianessAware(fileContent+28);
  if (bitsPerPixel != 24) return false;
  setSize(pictureSize);
  return readDataMatrix((const sc8 *) fileContent);
}

