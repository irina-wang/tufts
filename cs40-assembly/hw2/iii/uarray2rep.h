/*****************************************
 * 
 * bit2rep.h
 * 
 * 
 * Authors    : Tianyi Ma -- tma02
 *              Mengqi Irina Wang -- mwang17 
 * Date       : 2019/09/19
 *
 *****************************************/

#ifndef UARRAY2REP_INCLUDED
#define UARRAY2REP_INCLUDED

#include "uarray.h"

#define T UArray2_T

struct T {
    int width; /* number of elements in ’elems’, at least 0 */
    int height;
    UArray_T uarray;
};

#undef T
#endif
