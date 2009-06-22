#ifndef BITMAP_FUNCS_H
#define BITMAP_FUNCS_H

inline ui32
min(const ui32& first, const ui32& second)
{
  return (first < second) ? first : second;
}

inline ui32
max(const ui32& first, const ui32& second)
{
  return (first > second) ? first : second;
}

inline ui32
getNumBy4bytesEndianessAware(const char * _input) /* It expects 4 bytes */
{
  return ( ((ui32)_input[0]) + ( ((ui32) _input[1]) << 8 )
  	  + ( ((ui32) _input[2]) << 16 ) + ( ((ui32) _input[3]) << 24 ) );
}

inline ui32
getNumBy2bytesEndianessAware(const char * _input) /* It expects 4 bytes */
{
  return ( ((ui32)_input[0]) + ( ((ui32) _input[1]) << 8 ) );
}

inline void 
putNumberEndianessAware(const ui32 _num, const ui32 _size, char * _output)
{
  int i = 0;
  for (i = 0; i < _size; i++) {
    _output[i] = ((_num >> (i*8)) & MASK);
  }
}

inline void 
putNumTo2bytesEndianessAware(const ui32 _num, char * _output)
{
  _output[0] = ( _num       & MASK);
  _output[1] = ((_num >> 8) & MASK);
}

inline void 
putNumTo4bytesEndianessAware(const ui32 _num, char * _output)
{
  _output[0] = ( _num        & MASK);
  _output[1] = ((_num >>  8) & MASK);
  _output[2] = ((_num >> 16) & MASK);
  _output[3] = ((_num >> 24) & MASK);
}

inline void 
putStringEndianessAware(const char * _string, const ui32 _size, char * _output)
{
  int i = 0;
  for (i = 0; i < _size; i++) {
    _output[i] = _string[i];
  }
}

inline void 
putStringTo4bytesEndianessAware(const char * _string, char * _output)
{
  _output[0] = _string[0];
  _output[1] = _string[1];
  _output[2] = _string[2];
  _output[3] = _string[3];
}

inline void 
putStringTo2bytesEndianessAware(const char * _string, char * _output)
{
  _output[0] = _string[0];
  _output[1] = _string[1];
}

#endif
