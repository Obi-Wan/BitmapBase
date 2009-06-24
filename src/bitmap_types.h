#ifndef BITMAP_TYPES_H
#define BITMAP_TYPES_H

#include <stddef.h>

#define COLOR_RED       (1<<0)
#define COLOR_GREEN     (1<<1)
#define COLOR_BLUE      (1<<2)

typedef unsigned char       uc8;
typedef signed char         sc8;

typedef unsigned short int  ui16;
typedef unsigned int        ui32;
typedef unsigned long int   ui64;

typedef signed short int    si16;
typedef signed int          si32;
typedef signed long int     si64;

typedef struct {
  si16 blue;
  si16 green;
  si16 red;
}                           si16_3;

typedef struct {
  si32 blue;
  si32 green;
  si32 red;
}                           si32_3;

typedef struct {
  si64 blue;
  si64 green;
  si64 red;
}                           si64_3;

typedef struct {
  uc8 blue;
  uc8 green;
  uc8 red;

  uc8 & getChannel(ui32 chan) {
//    return ( (chan & COLOR_RED) ? &red : ( (chan & COLOR_GREEN) ? &green : &blue )  );
    switch (chan) {
      case COLOR_RED:
        return red;
      case COLOR_GREEN:
        return green;
      case COLOR_BLUE:
        return blue;
    }
  }
}                           pixel24;

typedef struct {
  ui32 width;
  ui32 height;
}                           size;

typedef struct coordinate {
  ui32 x;
  ui32 y;

  coordinate(ui32 _x, ui32 _y) : x(_x), y(_y) { }
  coordinate(const coordinate & coords) : x(coords.x), y(coords.y) { }
}                           coordinate;

typedef struct rel_coordinate {
  si32 x;
  si32 y;

  rel_coordinate(si32 _x, si32 _y) : x(_x), y(_y) { }
  rel_coordinate(const rel_coordinate & coords) : x(coords.x), y(coords.y) { }
  rel_coordinate(const coordinate & coords) : x(coords.x), y(coords.y) { }
}                           rel_coordinate;

typedef uc8 padding;

#define MASK 255

#endif
