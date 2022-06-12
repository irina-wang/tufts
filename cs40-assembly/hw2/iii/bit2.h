/*****************************************
 * 
 * uarray2.h
 * 
 * 
 * Authors    : Tianyi Ma -- tma02
 *              Mengqi Irina Wang -- mwang17 
 * Date       : 2019/09/19
 *
 *****************************************/

#ifndef BIT2_INCLUDED
#define BIT2_INCLUDED

#define T Bit2_T
typedef struct T *T;

/* Bit2_new
 *   Allocates and initializes a new 2D array of bit with the given width 
 * and height
 *
 *  Parameters   : an integer of array's width, an integer of array's height
 *  Return       : the new 2D bit array object
 *  Expectations : 1) width, height are non-negative integers
 */
extern T Bit2_new (int width, int height);

/*
 * Bit2_free
 *   frees the memory of the 2D bit array
 *
 *  Parameters   : a pointer to the array to be freed
 *  Return       : nothing
 *  Expectations : 1) bit2 is not NULL
 */
extern void Bit2_free(T *bit2);

/*
 * Bit2_width
 *   return the width of the 2D bit array
 *
 *  Parameters   : a 2D bit array, bit2
 *  Return       : an integer of the width of the array
 *  Expectations : 1) bit2 is not NULL
 */
extern int Bit2_width(T bit2);

/*
 * Bit2_height
 *   return the height of the 2D bit array
 *
 *  Parameters   : a 2D bit array, bit2
 *  Return       : an integer of the width of the array
 *  Expectations : 1) bit2 is not NULL
 */
extern int Bit2_height(T bit2);

/*
 * Bit2_put
 *   return the previous value of element at the given col and row,
 * and replace it with the newly given value
 *
 *  Parameters   : a 2D bit array, bit2
 *  Return       : the previous value of element at the given position
 *  Expectations : 1) col is less than bit2's width
 *                 2) row is less than bit2's height
 *                 3) both col and row are greater than 0
 *                 4) bit2 is not NULL
 */
extern int Bit2_put(T bit2, int col, int row, int val);

/*
 * Bit2_get
 *   return the value of element at the given col and row
 *
 *  Parameters   : a 2D bit array, bit2, an integer of column, 
 *                 an integer of row
 *  Return       : the value of element at the given position
 *  Expectations : 1) col is less than bit2's width
 *                 2) row is less than bit2's height
 *                 3) both col and row are greater than 0
 *                 4) bit2 is not NULL
 */
extern int Bit2_get(T bit2, int col, int row);

/*
 * Bit2_map_row_major
 *   calls an apply function to every entry in the bit array in the 
 * row-major(Column indices vary more rapidly than row indices) order. 
 * 
 *  Parameters   : a 2D bit array, bit2, the apply function, a void pointer 
 *                 closure
 *  Return       : nothing
 *  Expectations : 1) bit2 array is not NULL (initialized)
 *                 2) apply function is not NULL
 */
extern void Bit2_map_row_major(T bit2, 
                               void apply(int col, int row, T bit2, int val, void *cl),
                               void *cl);

/*
 * Bit2_map_col_major
 *   calls an apply function to every entry in the bit array in the 
 * column-major(row indices vary more rapidly than column indices) order. 
 * 
*  Parameters   : a 2D bit array, bit2, the apply function, a void pointer 
 *                 closure
*  Return       : nothing
*  Expectations : 1) bit2 array is not NULL (initialized)
    *                 2) apply function is not NULL
 */
extern void Bit2_map_col_major(T bit2, 
                               void apply(int col, int row, T bit2, int val, void *cl),
                               void *cl);

#undef T
#endif
