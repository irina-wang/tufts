#ifndef BIT2REP_INCLUDED
#define BIT2REP_INCLUDED

#include "bit.h"
 
#define T Bit2_T
 
struct T {
    int width;
    int height;
    Bit_T bitmap;
};
 
#undef T
#endif
