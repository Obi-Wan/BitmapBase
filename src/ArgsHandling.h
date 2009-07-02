/* 
 * File:   ArgsHandling.h
 * Author: ben
 *
 * Created on 2 luglio 2009, 18.17
 */

#ifndef _ARGSHANDLING_H
#define	_ARGSHANDLING_H

#include "bitmap_types.h"

#include <map>
#include <set>
//#include <vector>
#include <string>

using namespace std;

//struct OptionProps {
//  ui16 numParams;
//  vector<string> params;
//  set<string> incompatList;
//};

enum Args {
  INPUT,
  OUTPUT,
  TRANSFORM
};

const static char * argsStrings[] = {
  "-input",
  "-output",
  "-transform"
};

class ArgsHandling {

  bool dirty;

  map<string, string> options;

public:
  ArgsHandling(si32 argc, char **argv);
  virtual ~ArgsHandling();

  const bool isDirty() const { return dirty; }

  const string & getOption(const ui32 & op) const {
    return options.at(argsStrings[op]);
  }
};

#endif	/* _ARGSHANDLING_H */

