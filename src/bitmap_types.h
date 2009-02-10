#ifndef BITMAP_TYPES_H
#define BITMAP_TYPES_H

typedef unsigned char		uc8;
typedef signed char		sc8;

typedef unsigned short int	ui16;
typedef unsigned int		ui32;
typedef unsigned long int	ui64;

typedef signed short int	si16;
typedef signed int		si32;
typedef signed long int		si64;

struct pixel24 {
  uc8 blue;
  uc8 green;
  uc8 red;
};

struct size {
  ui32 width;
  ui32 height;
};

typedef uc8 padding;

#define MASK 255

#endif
