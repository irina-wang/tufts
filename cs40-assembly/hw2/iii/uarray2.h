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

#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED

#define T UArray2_T
typedef struct T *T;

/*
 * UArray2_new
 *   Allocates and initializes a new 2D array with the given width, height and
 * element size
 *
 *  Parameters   : an integer of array's width, an integer of array's height, 
 *                 an integer of each element's size
 *  Return       : the new array object
 *  Expectations : 1) width, height are non-negative integers
 *                 2) size should be a positive integer
 */
extern T UArray2_new (int width, int height, int size);

/*
 * UArray2_free
 *   frees the memory of the 2D array
 *
 *  Parameters   : a pointer to the array to be freed
 *  Return       : nothing
 *  Expectations : 1) uarray2 is not NULL
 */
extern void UArray2_free(T *uarray2);

/*
 * UArray2_width
 *   return the width of the 2D array
 *
 *  Parameters   : a 2D array, uarray2
 *  Return       : an integer of the width of the array
 *  Expectations : 1) uarray2 is not NULL
 */
extern int UArray2_width(T uarray2);

/*
 * UArray2_height
 *   return the height of the 2D array
 *
 *  Parameters   : a 2D array, uarray2
 *  Return       : an integer of the width of the array
 *  Expectations : 1) uarray2 is not NULL
 */
extern int UArray2_height(T uarray2);

/*
 * UArray2_size
 *   return the size of each element of the 2D array
 *
 *  Parameters   : a 2D array, uarray2
 *  Return       : an integer of the size of each element in the array
 *  Expectations : 1) uarray2 is not NULL
 */
extern int UArray2_size (T uarray2);

/*
 * UArray2_at
 *   return the pointer to element at the given col and row
 *
 *  Parameters   : a 2D array, uarray2
 *  Return       : a pointer to the element at the given position
 *  Expectations : 1) col is less than uarray2's width
 *                 2) row is less than uarray2's height
 *                 3) both col and row are greater than 0
 *                 4) uarray2 is not NULL
 */
void *UArray2_at(T uarray2, int col, int row);

/*
 * UArray2_map_row_major
 *   calls an apply function to every entry in array in the row-major(Column 
 * indices vary more rapidly than row indices) order. 
 * 
 *  Parameters   : a 2D array, uarray2, the apply function, a void pointer 
 *                 closure
 *  Return       : nothing
 *  Expectations : 1) uarray2 is not NULL (initialized)
 *                 2) apply function is not NULL
 */
extern void UArray2_map_row_major(T uarray2, 
                                  void apply(int col, int row, T uarray2, void *ptr, void *cl),
                                  void *cl);

/*
 * UArray2_map_col_major
 *   calls an apply function to every entry in array in the column-major(row 
 * indices vary more rapidly than column indices) order. 
 * 
 *  Parameters   : a 2D array, uarray2, the apply function, a void pointer 
 *                 closure
 *  Return       : nothing
 *  Expectations : 1) uarray2 is not NULL (initialized)
     *                 2) apply function is not NULL
 */
extern void UArray2_map_col_major(T uarray2, 
                                  void apply(int col, int row, T uarray2, void *ptr, void *cl),
                                  void *cl);

#undef T
#endif
