#include "DiskIO.h"
#include "bitmap_funcs.h"

//#define DEBUG

/////////////////////////////////////////////////////
// Contructors
////////////////////////////////////////////////////

DiskIO::DiskIO(const DiskOperation _op,const sc8 * _filename,
		BitmapFile * _data)
		: op(_op), filename(_filename), data(_data) {}

/////////////////////////////////////////////////////
// Other Functions
////////////////////////////////////////////////////

DiskIO * 
DiskIO::createFileSocket(const DiskOperation _op, const sc8 * _filename,
			BitmapFile * _data)
{
  /* Here I could put my control code */
  return new DiskIO(_op,_filename,_data);
}

bool 
DiskIO::read() {
  if ((READ & op) && filename && data) {
    
    FILE * fileInput = fopen((const char *) filename,"r");
    
    if (fileInput != NULL) {
      if (( (getc(fileInput) != 'B') || (getc(fileInput) != 'M') )) {
        fclose(fileInput);
        return false;
      }
#ifdef DEBUG
      printf("Ok è un bitmap\n");
#endif

      char * fileContent = new char[4];
      if ( fread(fileContent,sizeof(char),4,fileInput) < 4 ) {
        fclose(fileInput);
        delete []fileContent;
        return false;
      }
      ui32 count = getNumBy4bytesEndianessAware(fileContent);
      delete []fileContent;
      rewind(fileInput);
#ifdef DEBUG
      printf("Ok ha dimensione %d in byte: \n",count);
#endif
      
      fileContent = new char[count];
      fread(fileContent,sizeof(char),count,fileInput);
      data->readBMPFile(count,fileContent);
      fclose(fileInput);
      delete []fileContent;
      return true;
    }
  }
  return false;
}

bool 
DiskIO::write() {
  if ((WRITE & op) && filename && data) {
    
    FILE * fileOutput = fopen((const char *) filename,"w");
    
    if (fileOutput != NULL) {
      const char * fileContent = data->printBMPFile();
      fwrite(fileContent,sizeof(char),data->getFileSize(),
    		fileOutput);
      fflush(fileOutput);
      delete []fileContent;
      return true;
    }
  }
  return false;
}

//#undef DEBUG

