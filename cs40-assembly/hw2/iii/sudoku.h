/*****************************************
 * 
 * sudoku.h
 * 
 * 
 * Authors    : Tianyi Ma -- tma02
 *              Mengqi Irina Wang -- mwang17 
 * Date       : 2019/09/19
 *
 *****************************************/

#ifndef SUDOKU_INCLUDED
#define SUDOKU_INCLUDED

#include <stdio.h>
#include "uarray2.h"

FILE *get_file(int, char**);
UArray2_T read_sudoku(FILE*);
int check_sudoku(UArray2_T);

#endif
