/* 
 * File:   ArgsHandling.h
 * Author: ben
 *
 * Created on 2 luglio 2009, 18.17
 */

#ifndef _ARGSHANDLING_H
#define	_ARGSHANDLING_H

#include "bitmap_types.h"
#include "transformations.h"

#include <map>
#include <set>
//#include <vector>
#include <string>

using namespace std;

#define FEATURE_INPUT   (1 << 0)
#define FEATURE_OUTPUT  (1 << 1)

//typedef pair< TransformType , ui32 > transformProps;

struct transformProps {
  TransformType type;
  ui32 features;
  string description;

  transformProps(const TransformType & t, const ui32 & f, const string & d)
          : type(t), features(f), description(d) {}
};

//struct OptionProps {
//  ui16 numParams;
//  vector<string> params;
//  set<string> incompatList;
//};

enum Args {
  INPUT,
  OUTPUT,
  TRANSFORM,
  HELP
};

const static char * argsStrings[] = {
  "-input",
  "-output",
  "-transform",
  "-help"
};

enum SubArgs {
  COLORS,
  THRESHOLD
};

const static char * subArgsStrings[] = {
  "-colors",
  "-threshold"
};

class Cfg {

  bool dirty;

  map<string, string> options;

  map<string, transformProps> trasformations;

public:
  Cfg(si32 argc, char **argv);
  virtual ~Cfg();

  const bool isDirty() const { return dirty; }

  const string & getOption(const ui32 & op) const {
    return options.at(argsStrings[op]);
  }
  const string & getSubOption(const ui32 & op) const {
    return options.at(subArgsStrings[op]);
  }

  const ui32 getFeatures() const;
  const TransformType getTrasform() const;
  void printHelp() const;
};

#endif	/* _ARGSHANDLING_H */

