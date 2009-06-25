#include "bitmap_file.h"
#include "bitmap_funcs.h"

#define DEBUG

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

BitmapFile::BitmapFile()
		: BitmapBase(0,0) {}

BitmapFile::BitmapFile(size _size)
		: BitmapBase(_size.width,_size.height) {}

BitmapFile::BitmapFile(size _size, pixel24 * _data)
		: BitmapBase(_size.width,_size.height,_data) {}


/////////////////////////////////////////////////////
// Other Functions
////////////////////////////////////////////////////

char * 
BitmapFile::printBMPFile() {

  // Setting the sizes
  const ui32 dataSize = getDataSize();
  const ui32 fileSize = getFileSize();
  
  // Allocated buffer space
  char * fileContent = new char[fileSize];

  //- Writing the Header -//
  // File Type
  putStringTo2bytesEndianessAware(TYPE_FILE_HEADER,fileContent);
  // File Size
  putNumTo4bytesEndianessAware(fileSize,fileContent+2);
  // Empty application specific data
  putStringEndianessAware(APPLICATION_SPECIFIC_DATA,
		  APPLICATION_SPECIFIC_DATA_SIZE,
		  fileContent+APPLICATION_SPECIFIC_DATA_OFFSET);
  // Header size info
  putNumTo4bytesEndianessAware(HEADER_SIZE,
		  fileContent+OFFSET_OF_DATA_OFFSET);
  putNumTo4bytesEndianessAware(REMAINING_HEADER_BYTES,
		  fileContent+REMAINING_HEADER_BYTES_OFFSET);
  // Image size data.
  putNumTo4bytesEndianessAware(getWidth(),fileContent+WIDTH_OF_BITMAP_OFFSET);
  putNumTo4bytesEndianessAware(getHeight(),fileContent+HEIGHT_OF_BITMAP_OFFSET);
  // Props that do not depend on us.
  putStringEndianessAware(STATIC_PROPS_HEADER1,
		  STATIC_PROPS_HEADER1_SIZE,
		  fileContent+STATIC_PROPS_HEADER1_OFFSET);
  // Data size info (padding included)
  putNumTo4bytesEndianessAware(dataSize,
		  fileContent+RAW_DATA_SPECIFICATION_OFFSET);
  // Props that do not depend on us 2.
  putStringEndianessAware(STATIC_PROPS_HEADER2,
		  STATIC_PROPS_HEADER2_SIZE,
		  fileContent+STATIC_PROPS_HEADER2_OFFSET);

  //- Writing the Data Matrix -//
  emitBMPMatrixDataToWrite(getDataSize(),fileContent + HEADER_SIZE);
  
  return fileContent;
}

bool
BitmapFile::readBMPFile(const ui32 _size,const char * fileContent) {

  // Offset from the start of file at which data is located
  const ui32 data_offset = getNumBy4bytesEndianessAware(fileContent+10);
  
  // size of the picture (and of the matrix)
  const size pictureSize = {
  		getNumBy4bytesEndianessAware(fileContent+18), 
		getNumBy4bytesEndianessAware(fileContent+22)
		};
#ifdef DEBUG
      printf("Dimensioni immagine: (%d,%d)\n",pictureSize.width,pictureSize.height);
#endif

  // Color Depth of the picture
  const ui16 bitsPerPixel = getNumBy2bytesEndianessAware(fileContent+28);
  
  // reads file and stores data in the matrix
  switch (bitsPerPixel) {
    case 16:
#ifdef DEBUG
      printf("Support for 16bit color depth, not implemented yet.\n");
#endif
      return false;
    case 24:
#ifdef DEBUG
      printf("Using support for 24bit color depth\n");
#endif
      // sets the new size of the matrix (to be moved out)
      setSize(pictureSize);
      // apllies it, cleaning the previous stored data (to be moved out)
      cleanAndRefreshMatrix();
      // reads file and stores data in the matrix
      return readDataMatrix24((const sc8 *) fileContent + data_offset);
    case 32:
#ifdef DEBUG
      printf("Support for 32bit color depth, not implemented yet.\n");
#endif
      return false;
  }
}

#undef DEBUG
