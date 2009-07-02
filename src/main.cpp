#include "bitmap_file.h"
#include "transformations.h"
#include "DiskIO.h"
#include "ArgsHandling.h"
#include <cstdio>

int main(si32 argc, char **argv) {

  ArgsHandling argsHandler(argc,argv);

  if (argsHandler.isDirty()) {
    return 1;
  } else {
    BitmapFile * theBitmap = new BitmapFile();

    DiskIO * reader =
            DiskIO::createFileSocket(READ,
                                     (const sc8 *)argsHandler.getOption(INPUT).c_str(),
                                     theBitmap);
    reader->read();

    theBitmap->applyTransform();

    DiskIO * writer =
            DiskIO::createFileSocket(WRITE,
                                     (const sc8 *)argsHandler.getOption(OUTPUT).c_str(),
                                     theBitmap);
    writer->write();
    return 0;
  }
}
