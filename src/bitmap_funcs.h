#ifndef BITMAP_FUNCS_H
#define BITMAP_FUNCS_H

#include "bitmap_types.h"
#include <math.h>

inline ui32
absMin(const ui32& first, const ui32& second)
{
  return (first < second) ? first : second;
}

inline ui32
absMax(const ui32& first, const ui32& second)
{
  return (first > second) ? first : second;
}

inline si32
min(const si32& first, const si32& second)
{
  return (first < second) ? first : second;
}

inline si32
max(const si32& first, const si32& second)
{
  return (first > second) ? first : second;
}

inline si32
distance(const rel_coordinate & coords) {
  return sqrt(coords.x * coords.x + coords.y * coords.y);
}

inline si32
distanceQuad(const rel_coordinate & coords) {
  return (coords.x * coords.x + coords.y * coords.y);
}

//-----------------------

inline ui32
getUIntBy4Char(const char * _input) /* It expects 4 bytes */
{
  return ( ( ((ui32) (_input[0] & MASK))       ) +
           ( ((ui32) (_input[1] & MASK)) << 8  ) +
           ( ((ui32) (_input[2] & MASK)) << 16 ) +
           ( ((ui32) (_input[3] & MASK)) << 24 ) );
}

inline ui32
getUIntBy2Char(const char * _input) /* It expects 2 bytes */
{
  return ( ( ((ui32) (_input[0] & MASK))      ) +
           ( ((ui32) (_input[1] & MASK)) << 8 ) );
}

inline void 
putUIntOfVarSize(const ui32 _num, const ui32 _size, char * _output)
{
  int i = 0;
  for (i = 0; i < _size; i++) {
    _output[i] = ((_num >> (i*8)) & MASK);
  }
}

inline void 
putUIntTo2Char(const ui32 _num, char * _output)
{
  _output[0] = ( _num       & MASK);
  _output[1] = ((_num >> 8) & MASK);
}

inline void 
putUIntTo4Char(const ui32 _num, char * _output)
{
  _output[0] = ( _num        & MASK);
  _output[1] = ((_num >>  8) & MASK);
  _output[2] = ((_num >> 16) & MASK);
  _output[3] = ((_num >> 24) & MASK);
}

inline void 
putStringOfVarSize(const char * _string, const ui32 _size, char * _output)
{
  int i = 0;
  for (i = 0; i < _size; i++) {
    _output[i] = _string[i];
  }
}

inline void 
putStringTo4Char(const char * _string, char * _output)
{
  _output[0] = _string[0];
  _output[1] = _string[1];
  _output[2] = _string[2];
  _output[3] = _string[3];
}

inline void 
putStringTo2Char(const char * _string, char * _output)
{
  _output[0] = _string[0];
  _output[1] = _string[1];
}

//-----------------------------

inline pixel24 *
getPointerRelCoords(pixel24 * matrix,const size & _size,
                    const coordinate & absCoords,
                    const rel_coordinate & relCoords) {
  return (matrix + (absCoords.y + relCoords.y) * _size.width +
          (absCoords.x + relCoords.x));
}

inline pixel24 *
getPointerAbsCoords(pixel24 * matrix, const size & _size,
                    const coordinate & coords) {
  return getPointerRelCoords(matrix,_size,coords,coordinate(0,0));
}

#endif
