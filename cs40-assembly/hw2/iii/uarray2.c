#include "uarray2.h"
#include "uarray2rep.h"
#include "uarray.h"
#include "mem.h"
#include <assert.h>
#include <stdio.h>

#define T UArray2_T

extern T UArray2_new (int width, int height, int size)
{
    /* Handles CRE in UArray implem */
    T array2;
    NEW(array2);
    array2->width = width;
    array2->height = height;
    array2->uarray = UArray_new(width * height, size);
    return array2;
}

extern void UArray2_free(T *uarray2)
{
    assert(uarray2 && *uarray2);
    UArray_free(&((*uarray2)->uarray));
    FREE(*uarray2);
}

extern int UArray2_width(T uarray2)
{
    assert(uarray2);
    return uarray2->width;
}

extern int UArray2_height(T uarray2)
{
    assert(uarray2);
    return uarray2->height;
}

extern int UArray2_size (T uarray2)
{
    assert(uarray2);
    return UArray_size(uarray2->uarray);
}

void *UArray2_at(T uarray2, int col, int row) 
{
    assert(uarray2 && uarray2->uarray);
    return UArray_at(uarray2->uarray, row * uarray2->width + col);
}

extern void UArray2_map_row_major(T uarray2, 
                                  void apply(int col, int row, T uarray2, void *ptr, void *cl),
                                  void *cl)
{
    assert(uarray2 && uarray2->uarray);
    assert(apply);
    for (int j = 0; j < uarray2->height; j++) {
        for (int i = 0; i < uarray2->width; i++) {
            apply(i, j, uarray2, UArray2_at(uarray2, i, j), cl);
        }
    }
}
extern void UArray2_map_col_major(T uarray2, 
                                  void apply(int col, int row, T uarray2, void *ptr, void *cl),
                                  void *cl)
{
    assert(uarray2 && uarray2->uarray);
    assert(apply);
    for (int i = 0; i < uarray2->width; i++) {
        for (int j = 0; j < uarray2->height; j++) {
            apply(i, j, uarray2, UArray2_at(uarray2, i, j), cl);
        }
    }
}

#undef T
