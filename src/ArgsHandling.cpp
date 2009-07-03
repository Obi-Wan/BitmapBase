/* 
 * File:   ArgsHandling.cpp
 * Author: ben
 * 
 * Created on 2 luglio 2009, 18.17
 */

#include <stdio.h>

#include "ArgsHandling.h"
#include "transformations.h"

typedef pair<string,string> option;
typedef pair<string,transformProps> feature;

Cfg::Cfg(si32 argc, char **argv) : dirty(false) {

  options.insert(option(argsStrings[INPUT],"prova.bmp"));
  options.insert(option(argsStrings[OUTPUT],"prova2.bmp"));
  options.insert(option(argsStrings[TRANSFORM],"satur"));
  options.insert(option(argsStrings[HELP],""));
  options.insert(option(subArgsStrings[COLORS],"16"));
  options.insert(option(subArgsStrings[THRESHOLD],"224"));

  trasformations.insert(
      feature(transfomNames[GRADIENT],
              transformProps(GRADIENT,
                             FEATURE_OUTPUT,
                             "")));
  trasformations.insert(
      feature(transfomNames[INVERSE_GRADIENT],
              transformProps(INVERSE_GRADIENT,
                             FEATURE_OUTPUT,
                             "")));
  trasformations.insert(
      feature(transfomNames[SIN_AND_GRADIENT],
              transformProps(SIN_AND_GRADIENT,
                             FEATURE_OUTPUT,
                             "")));
  trasformations.insert(
      feature(transfomNames[SIN_ALL_CHANNELS],
              transformProps(SIN_ALL_CHANNELS,
                             FEATURE_OUTPUT,
                             "Outputs a sinusoidal theme")));
  trasformations.insert(
      feature(transfomNames[TRANSPOSE],
              transformProps(TRANSPOSE,
                             FEATURE_OUTPUT | FEATURE_INPUT,
                             "Trasposes the matrix")));
  trasformations.insert(
      feature(transfomNames[SATURATION],
              transformProps(SATURATION,
                             FEATURE_OUTPUT | FEATURE_INPUT,
                             "Saturates")));
  trasformations.insert(
      feature(transfomNames[DECOLORIFY],
              transformProps(DECOLORIFY,
                             FEATURE_OUTPUT | FEATURE_INPUT,
                             "Decreases the number of colors")));
  trasformations.insert(
      feature(transfomNames[SIN_VERT_WAVE],
              transformProps(SIN_VERT_WAVE,
                             FEATURE_OUTPUT | FEATURE_INPUT,
                             "Makes the pixel waving")));

  map<string,string>::iterator iterOption;
  string op;
  for (ui32 cont = 1; cont < argc; cont++) {
    iterOption = options.find(string(argv[cont]));
    if (iterOption != options.end()) {
      op = iterOption->first;
      if (op == argsStrings[HELP]) {
        dirty = true;
      } else if (++cont < argc) {
        options[op] = string(argv[cont]);
      } else {
        printf("Malformed option: %s\n",argv[--cont]);
        dirty = true;
      }
    } else {
      printf("Unexisting option: %s\n",argv[cont]);
      dirty = true;
    }
  }

  if (trasformations.find( options.find(string(argsStrings[TRANSFORM]))->second)
          == trasformations.end()) {
    printf("Malformed transform option: %s\n",
           options.find(string(argsStrings[TRANSFORM]))->second.c_str());
    dirty = true;
  }
}

Cfg::~Cfg() {
  options.clear();
}

const ui32
Cfg::getFeatures() const {
  return trasformations.find(options.find(argsStrings[TRANSFORM])->second)
          ->second.features;
}

const TransformType
Cfg::getTrasform() const {
  return trasformations.find(options.find(argsStrings[TRANSFORM])->second)
          ->second.type;
}

void
Cfg::printHelp() const {
  printf("These are the options you can specify:\n"
          " %s : specify the input file.\n",argsStrings[INPUT]);
  printf(" %s : specify the output file.\n",argsStrings[OUTPUT]);
  printf(" %s : specify the transformation to operate. These are:\n",
         argsStrings[TRANSFORM]);
  for (map<string, transformProps>::const_iterator it = trasformations.begin();
       it != trasformations.end(); it++)
  {
    printf("  * %s : %s\n", it->first.c_str(), it->second.description.c_str());
  }

}