/***************************************************************************
 *
 * brightness.c
 * 
 * By Yichen Wei <ywei04> and Mengqi Wang (mwang17)
 * 
 * Summary :
 * 
 * This file is used to print out a single 
 * newline-terminated line containing the average brightness of the supplied
 * image.
 * 
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <pnmrdr.h>

double compute_brightness(FILE *img_file);
FILE *open_file(char *filename);


/* main function */
int main(int argc, char *argv[])
{
    Except_T too_many_files = {
        "Too many file names provided."
    };

    if (argc == 1){
        double brightness = compute_brightness(stdin);
        printf("The average brightness is: %.3f\n", brightness);
    } else if (argc > 2){
        RAISE(too_many_files);
    } else if (argc == 2) {
        FILE *file = open_file(argv[1]);
        double brightness = compute_brightness(file);
        printf("The average brightness is: %.3f\n", brightness);
        fclose(file);
    }
    return EXIT_SUCCESS;
}

/* function open_file
 * input: A string of filename.
 * purpose: opens the file and report if the operation is successful.
 * output: a pointer to a file.
 */
FILE *open_file(char *filename)
{
    FILE *_file = fopen(filename, "r");

    // if the file is not opened successfully, quit.
    assert(_file != NULL);

    // otherwise, return.
    return _file;
}

/* function compute_brightness
 * computes the brightness of the image file.
 * input: img_file, the file pointer where we should read from.
 * output: the average brightness of the file.
 * 
 */
double compute_brightness(FILE *img_file)
{
    // direct the file ptr to the library.
    Pnmrdr_T img_map = Pnmrdr_new(img_file);

    // get the basic info of the img.
    Pnmrdr_mapdata img_info = Pnmrdr_data(img_map);
    
    // we are supposed to process a greyscale so if it's not we exit.
    assert(img_info.type == Pnmrdr_gray);
    
    // The image must have more than 0 pixels.
    assert(img_info.height > 0);
    assert(img_info.width > 0);

    // the sum of the average of each row
    unsigned long total_sum = 0;

    for (unsigned i = 0; i < img_info.height; i++) {
        // the sum of average of pixels in each row
        unsigned long row_sum = 0;

        for (unsigned int j = 0; j < img_info.width; j++) {
            // add brightness of this pixel to the sum of this row
            row_sum += Pnmrdr_get(img_map);
        }
        // compute the average of current row and add
        total_sum += row_sum / img_info.width;
    }

    double brightness = (double) total_sum / img_info.height / 
            img_info.denominator;
    
    // free
    Pnmrdr_free(&img_map);

    return brightness;
}
