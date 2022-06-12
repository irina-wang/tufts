/***************************************************************************
 *
 * readaline.c
 * 
 * By Yichen Wei <ywei04> and Mengqi Wang (mwang17)
 * 
 * Summary :
 * 
 * This file is an implementation of readaline, which
 * reads a single line of input from file inputfd.
 * 
 * 
 * ref: https://stackoverflow.com/questions/3463426
 *
 * It is the responsibility of the caller of readaline to free the 
 *     array using free.
 * 
 *************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <except.h>

/* 
 * readaline(FILE *inputfd, char **dataapp)
 * 
 * Parameter : xxxxxxxxxxxxxx
 * Purpose   : To read in from the lines 
 * Return    : xxxxxxxxxxxxx
 * 
 * Note      : It's called by the main function
 */
size_t readaline(FILE *inputfd, char **dataapp)
{
    char c1, c2;
    const Except_T file_error = {
        "Unexpected file read error."
    };

    /* EOF? just return 0. Base case. */
    if (feof(inputfd)) {
        *dataapp = NULL;
        return 0;
    }
    
    /* Set the length. */
    size_t length = 0;

    fpos_t line_begin;
    int result = fgetpos(inputfd, &line_begin);
    assert(result == 0);

    /* read in one char at a time. */
    while (c1 = getc(inputfd), c1 != EOF && c1!= '\n') {
        length ++;
    }

    result = fsetpos(inputfd, &line_begin);
    assert(result == 0);

    /* allocate memory. This needs to be freed by the client. */
    char *data = (char *) malloc(length + 1); //要不要标注一下多allocate1一个for \0

    for (size_t i = 0; i < length; i++) {
        c2 = getc(inputfd);
        if (c2 == EOF || c2 == '\n') {
            RAISE(file_error);
        } else {
            data[i] = c2;
        }
    }

    data[length] = '\0';

    // skip this char.
    getc(inputfd);

    /* assign the string back */
    *dataapp = data;

    return length;
}

