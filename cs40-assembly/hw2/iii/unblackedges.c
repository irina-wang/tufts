/*****************************************
 * 
 * unblackedge.c
 * 
 * 
 * Authors    : Tianyi Ma -- tma02
 *              Mengqi Irina Wang -- mwang17 
 * Date       : 2019/09/21
 *
 *****************************************/

#include "unblackedges.h"
#include "pnmrdr.h"
#include "bit2.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <assert.h>


int main(int argc, char** argv) {
    FILE *input = get_file(argc, argv);
    Bit2_T img = pbm_read(input);
    remove_edge(img);
    /* 啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊
    测试阶段还是用下面这行，我忘了问如果input
    是stdin的话output文件应该叫什么名字orz  */
    pbm_write(fopen("unblack_new.pbm", "w"), img);
    return EXIT_SUCCESS;
}

/*
 * get_file
 *   return a pointer to the file to be read in
 *   
 * Parameter   : int argc, num of arguments, char** argv, pointer to the filename
 *               string
 * Return      : pointer to the File
 * Expectation : 1) if there's only one argument, take filename from standard 
 *                  input
 *               2) if there's two arguments, take the second as filename
 *               3) there shouldn't be more than 2 or less than 1 argument
 */
FILE *get_file(int argc, char** argv) {
    if (argc == 1) return stdin;
    else if (argc == 2) return fopen(argv[1], "r");
    else return NULL;
}


/*
 * pbm_read
 *   
 * 
 * Parameter   : FILE * inputfp, pointer to a file
 * Return      : a bit map img
 * Expectation : 1) width, height equal 0
 *               2) denominator is bigger than 1
 */
Bit2_T pbm_read(FILE *inputfp) {
    /* Pnmrdr_new will raise exceptions if inputfp is NULL 啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊是这样吗 */
    Pnmrdr_T reader = Pnmrdr_new(inputfp);
    int width = Pnmrdr_data(reader).width,
        height = Pnmrdr_data(reader).height;

    /* check width, height and denominator */
    if (width == 0 || height == 0 || Pnmrdr_data(reader).denominator > 1) {
        Pnmrdr_free(&reader);
        /* 会到这一步吗 还是new 的时候就raise呀 啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊是这样吗 */
        fprintf(stderr, "ERROR: Image file bad format.\n");
        exit(EXIT_FAILURE);
    }

    /* initialize a bit map and read in data */
    Bit2_T img = Bit2_new(width, height);
    Bit2_map_row_major(img, read_in, reader);
    Pnmrdr_free(&reader);

    /* close file */
    fclose(inputfp);
    return img;
}

/*
 * read_in
 *   get data from Pnmrdr and put in the bit map
 * 
 * Parameter   : int col, column, int row, row, Bit2_T bit2, the bitmap, int 
 *               val, value in each pixel, void *reader, void pointer to the 
 *               reader
 * Return      : nothing
 * Expectation : 1) 啊啊啊啊啊啊啊啊啊啊啊或许 col and row excess the maximum col and row in the bit2 bitmap
 * 
 */
void read_in(int col, int row, Bit2_T bit2, int val, void *reader) {
    /* surpress unused warning */
    (void) val;
    Bit2_put(bit2, col, row, Pnmrdr_get((Pnmrdr_T)reader));
}


/*
 * remove_edge
 *   remove edges from the bitmap image by checking from outside towards the 
 * center. First mark the black edges from the top and bottom row, as well as 
 * from the left column and right column. 
 * 
* Parameter   : a bitmap img
* Return      : nothing
* Expectation : 1) 啊啊啊啊啊啊啊啊啊啊啊或许 col and row shouldn't be 0?
 *               2) bottom row and the top row are the same when there's only
 *                  one row
*               3) left column and right column are the same when there's only
 *                  one column
 */
void remove_edge(Bit2_T img) {
    /* get width and length from bitmap */
    int width = Bit2_width(img), height = Bit2_height(img);

    /* create a new bitmap of same size to mark the checked pixels */
    // 啊啊啊啊啊啊啊啊啊啊啊啊mark 要不要叫 mark_map 什么的我后面突然恍惚了 
    Bit2_T mark = Bit2_new(width, height);
    
    /* * * * * * * * * * * * * * * * * * * * * *
     *  check the pixels on the sides and      *
     *  mark on the new bitmap if it's an edge *
     * * * * * * * * * * * * * * * * * * * * * */

    /* check the top and bottom row */
    for (int i = 0; i < width; i++) {
        /* if the pixel in the top row isn't white */
        if (Bit2_get(img, i, 0) != 0) 
            Bit2_put(mark, i, 0, 1);
        /* if the pixel in the bottom row isn't white 
           (check in advance if there's only one row)*/
        if (height > 1 && (Bit2_get(img, i, height - 1) != 0))
            Bit2_put(mark, i, height - 1, 1);
    }
    /* check the left and right column */
    for (int i = 0; i < height; i++) {
        /* if the pixel in the left column isn't white */
        if (Bit2_get(img, 0, i) != 0) 
            Bit2_put(mark, 0, i, 1);
        /* if the pixel in the right column isn't white 
           (check in advance if there's only one column) */
        if (width > 1 && (Bit2_get(img, width - 1, i) != 0))
            Bit2_put(mark, width - 1, i, 1);
    }

    /* scan the whole image and mark black edges */
    scan_img(img, mark, width, height);

    /* map through the image again and mark unmarked pixels white */
    Bit2_map_row_major(mark, modify_img, img);
    Bit2_free(&mark);
}

/*
 * modify_img
 *   adjust the unmarked pixels (those shouldn't be cleared) into white
 *   
 * Parameter   : int col, column, int row, row, Bit2_T bit2, the bitmap, int 
 *               val, value, void *img, void pointer to img
 * Return      : nothing
 * Expectation : 1) 啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊
 * 
 */
/* 啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊用mapping来修改原来的图片（用在上面👆） */
void modify_img(int col, int row, Bit2_T bit2, int val, void *img) {
    /* surpress unused warnings */
    (void) bit2;
    
    /* mark the pixel as white if it's unmarked */
    if (val != 0) 
        Bit2_put((Bit2_T)img, col, row, 0);
}


/*
 * check_neighbor
 *   return true if any of the current pixel's neighbour is an black edge
 * 
 * Parameter   : the marking bitmap mark, int col, column, int row, row
 * Return      : boolean, true when any of the curr pixel's neighbour is 
 *               an black edge, and otherwise false
 * Expectation : 1) col should be an integer that's bigger than 0 and smaller 
 *                  than the upper bound of the mark bitmap's width
 *               2) row should be an integer that's bigger than 0 and smaller 
 *                  than the upper bound of the mark bitmap's height
 */
bool check_neighbor(Bit2_T mark, int col, int row) {
    /* check left neighbour */
    if (col > 0 && Bit2_get(mark, col - 1, row) != 0) 
        return true;
    /* check up neighbour */
    if (row > 0 && Bit2_get(mark, col, row - 1) != 0) 
        return true;
    /* check right neighbour */
    if (col + 1 < Bit2_width(mark) && Bit2_get(mark, col + 1, row) != 0) 
        return true;
    /* check neighbour below */
    if (row + 1 < Bit2_height(mark) && Bit2_get(mark, col, row + 1) != 0) 
        return true;
    return false;
}

/*
 * scan_img
 *   get the pixel in img bitmap and check its neightbour in the mark bitmap,
 * if it's both black then mark it black in the mark bitmap.  
 * 
 * 
 */
/* 勉强把这个缩成了三十行... 我再想想有什么别的暴力算法 */
void scan_img(Bit2_T img, Bit2_T mark, int width, int height) {
    int os_limit = height > width ? width : height;
    for (int os = 1; os < os_limit - 1; os++) {
        /* checking horizontally */ 
        for (int i = 0; i < width; i++) { // 啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊这个是不是从1开始比较较好呀， since'边边已经被查过了， 而且这样width就不用-i再减1了
            /* starting from the second(现在是first) row and the second column */
            if (Bit2_get(img, i, os) != 0 && check_neighbor(mark, i, os))
                Bit2_put(mark, i, os, 1);
            /* starting from the second row and second（现在是first） last column */
            if (Bit2_get(img, width - i - 1, os) != 0 &&
                check_neighbor(mark, width - i - 1, os))
                Bit2_put(mark, width - i - 1, os, 1);
            /* starting from the second(现在是first) last row and second column */
            if (Bit2_get(img, i, height - os - 1) != 0 &&
                check_neighbor(mark, i, height - os - 1)) 
                Bit2_put(mark, i, height - os - 1, 1);
            /* starting from the second last row and second last column */
            // 啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊
            // 这里会 seg fault如果只有 1 个pixel 吧 因为 height - os - 1 = 1- 2 = -1
            if (Bit2_get(img, width - i - 1, height - os - 1) != 0 && 
                check_neighbor(mark, width - i - 1, height - os - 1)) 
                Bit2_put(mark, width - i - 1, height - os - 1, 1);
        }
        /* checking vertically */ 
        for (int i = 0; i < height; i++) {
            if (Bit2_get(img, os, i) != 0 && check_neighbor(mark, os, i)) 
                Bit2_put(mark, os, i, 1);
            if (Bit2_get(img, os, height - i - 1) != 0 && 
                check_neighbor(mark, os, height - i - 1)) 
                Bit2_put(mark, os, height - i - 1, 1);
            if (Bit2_get(img, width - os - 1, i) != 0 &&
                check_neighbor(mark, width - os - 1, i))
                Bit2_put(mark, width - os - 1, i, 1);
            if (Bit2_get(img, width - os - 1, height - i - 1) != 0 &&
                check_neighbor(mark, width - os - 1, height - i - 1))
                Bit2_put(mark, width - os - 1, height - i - 1, 1);
        }
    }
}

/*
 * pbm_write
 *   print the image with black edges out to the output file
 * 
 * Parameter   : file pointer outputfp to the file, Bit2_T bitmap, the marked 
 *               bitmap 
 * Return      : nothing
 * Expectation : 1) raise when pointer to the outputfp is NULL
 */
void pbm_write(FILE *outputfp, Bit2_T bitmap) {
    assert(outputfp);
    int width = Bit2_width(bitmap), height = Bit2_height(bitmap);
    fprintf(outputfp, "P1\n%d %d\n", width, height);
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) { 
            fprintf(outputfp, "%d ", Bit2_get(bitmap, col, row));
        }
        fprintf(outputfp, "\n");
    }

    /* free the bitmap */
    Bit2_free(&bitmap);
    fclose(outputfp);
}
