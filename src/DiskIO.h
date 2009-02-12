#ifndef DISK_IO_H
#define DISK_IO_H

#include "bitmap_file.h"
#include <cstdio>

enum DiskOperation {
  READ	=		   1,
  WRITE	=	      (1<<1),
  RW	=	(READ+WRITE)
};

class DiskIO {
  const sc8 * filename;
  BitmapFile * data;
  DiskOperation op;

  DiskIO(const DiskOperation _op, const sc8 * _filename = NULL, BitmapFile * _data = NULL);
public:
  /* Mi servirà per controlli sui file */
  static DiskIO * createFileSocket(const DiskOperation _op,
  		const sc8 * _filename = NULL,BitmapFile * _data = NULL);
  
  bool read();
  bool write();

  bool hasData() { return data; }
  bool hasFilename() { return filename; }

  BitmapFile * getData() { return data; }
  const sc8 * getFilename() { return filename; }

  bool fileExists() {
    if (!filename) return false;
    FILE * test = fopen((const char *) filename,"r");
    if (test != NULL) {
      fclose(test);
      return true;
    }
    return false;
  }
};

#endif
