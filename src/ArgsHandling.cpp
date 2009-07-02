/* 
 * File:   ArgsHandling.cpp
 * Author: ben
 * 
 * Created on 2 luglio 2009, 18.17
 */

#include <stdio.h>

#include "ArgsHandling.h"

typedef pair<string,string> option;

ArgsHandling::ArgsHandling(si32 argc, char **argv) : dirty(false) {

  options.insert(option(argsStrings[INPUT],"prova.bmp"));
  options.insert(option(argsStrings[OUTPUT],"prova2.bmp"));
  options.insert(option(argsStrings[TRANSFORM],"saturation"));

  map<string,string>::iterator iterOption;
  string op;
  for (ui32 cont = 1; cont < argc; cont++) {
    iterOption = options.find(string(argv[cont]));
    if (iterOption != options.end()) {
      op = iterOption->first;
      if (++cont < argc) {
        options[op] = string(argv[cont]);
      } else {
        printf("Malformed option\n");
        dirty = true;
      }
    } else {
      printf("Unexisting option\n");
      dirty = true;
    }
  }
}

ArgsHandling::~ArgsHandling() {
  options.clear();
}