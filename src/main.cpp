#include "bitmap_file.h"
#include "transformations.h"
#include "DiskIO.h"
#include "ArgsHandling.h"
#include <cstdio>

int main(si32 argc, char **argv) {

  Cfg cfgHandler(argc,argv);

  if (cfgHandler.isDirty()) {
    cfgHandler.printHelp();
    return 0;
  } else {
    BitmapFile * theBitmap = new BitmapFile();

    ui32 features = cfgHandler.getFeatures();

    if (features & FEATURE_INPUT) {
      DiskIO * reader =
              DiskIO::createFileSocket(READ,
                                       (const sc8 *)cfgHandler.getOption(INPUT).c_str(),
                                       theBitmap);
      if (!reader->read()) {
        delete theBitmap;
        return 1;
      }
    }

    theBitmap->applyTransform(cfgHandler);

    if (features & FEATURE_OUTPUT) {
      DiskIO * writer =
              DiskIO::createFileSocket(WRITE,
                                       (const sc8 *)cfgHandler.getOption(OUTPUT).c_str(),
                                       theBitmap);
      if (!writer->write()) {
        delete theBitmap;
        return 1;
      }
    }

    delete theBitmap;
    return 0;
  }
}
