/*****************************************
 * 
 * sudoku.c
 * 
 * 
 * Authors    : Tianyi Ma -- tma02
 *              Mengqi Irina Wang -- mwang17 
 * Date       : 2019/09/21
 *
 *****************************************/

#include "sudoku.h"
#include "pnmrdr.h"
#include "except.h"
#include "uarray2.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

int main(int argc, char** argv) {
    FILE *sudoku = get_file(argc, argv);
    //assert(sudoku);
    return check_sudoku(read_sudoku(sudoku));
}

/*
 * get_file
 *   returns the pointer to the file to be read either from standard input or 
 * the filename argument
 * 
 *  Parameters   : int argc, number of arguments, char** argv, a pointer that 
 *                 points to a pointer to a char, filename
 *  Return       : a pointer to the file to be read
 *  Expectations : 1) argc should be 1 or 2
 */
FILE *get_file(int argc, char** argv) {
    if (argc == 1) return stdin;
    else if (argc == 2) return fopen(argv[1], "r");
    else return NULL;
}

/*
 * read_sudoku
 *   converts the content in the sudoku file into a 2D array and returns it 
 * 
 *  Parameters   : a pointer to the sudoku file
 *  Return       : the sudoku 2D array
 *  Expectations : 1) Pnmrdr_data's width and height should be 9
 *                 2) Pnmrdr_data‘s denominator should be 9
 */
UArray2_T read_sudoku(FILE* sudoku) {
    Pnmrdr_T reader = Pnmrdr_new(sudoku);       // 啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊May raise exception

    /* check if the greymap represents a standard sudoku problem*/
    if (!(Pnmrdr_data(reader).width == 9 && Pnmrdr_data(reader).height == 9) ||
        Pnmrdr_data(reader).denominator != 9) {
        Pnmrdr_free(&reader);
        exit(EXIT_FAILURE);
    }

    /* Allocate memory for the new 2D array*/ 
    UArray2_T array = UArray2_new(9, 9, sizeof(int));
    /* 啊啊啊啊啊啊啊啊啊啊啊啊啊啊TODO: Use mapping function instead */

    /* Assign value to each element in the new 2D array */
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            *((int *)UArray2_at(array, col, row)) = Pnmrdr_get(reader);
        }
    }

    /* Frees the memory of reader */
    Pnmrdr_free(&reader);

    /* Close file */
    fclose(sudoku);
    return array;
}


/*
 * check_sudoku
 *   check if the sudoku is done correctly -- 1-9 only appear once in every 
 * column, row and three-by-three submap.
 * 
 *  Parameters   : the sudoku 2D array to be checked 
 *  Return       : int, with 0 indicating a solved sudoku and 1 indicating 
 *                 an unsolved sudoku
 *  Expectations : 我不知道！
 */
int check_sudoku(UArray2_T array) {
    /* Initializes bool maps to check if any num doesn't appear */
    bool submap[3][3][9]; /* first two indicate submap, 
                             third indicates solution */
    bool col_sum[9][9]; /* first indicates col num, second indicates solution */
    bool row_sum[9][9]; /* first indicates row num, second indicates solution */
    
    /* Current number */

    int curr_num;
    /* 啊啊啊啊啊啊啊啊啊啊啊啊啊啊TODO: Use mapping function */
    /* Initializes three checking maps with false */
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 9; k++) {
                submap[i][j][k] = false;
                col_sum[i * 3 + j][k] = false;
                row_sum[i * 3 + j][k] = false;
            }
        }
    }

    /* checks every element in the array and updates the checking map */
    for (int col = 0; col < 9; col++) {
        for (int row = 0; row < 9; row++) {
            curr_num = *((int *)UArray2_at(array, col, row));
            /* Dividing 3 allows 0-2, 3-5, 6-8 to be grouped together ;
               curr_num - 1 so that it will be 0-8 in the array */
            submap[col/3][row/3][curr_num - 1] = true;
            col_sum[col][curr_num - 1] = true;
            row_sum[row][curr_num - 1] = true;
        }
    }
    UArray2_free(&array);

    /* go through the checking map and determine if sudoku is solved */
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 9; k++) {
                if ((submap[i][j][k] == false) ||
                    (col_sum[i * 3 + j][k] == false) ||
                    (row_sum[i * 3 + j][k] == false))
                    return 1;
            }
        }
    }
    return 0;
}
