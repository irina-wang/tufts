/***************************************************************************
 *
 * readaline.h
 * 
 * By Yichen Wei <ywei04> and Mengqi Wang (mwang17)
 * 
 * Summary :
 * 
 * This file is an interface of readaline, which
 * reads a single line of input from file inputfd, 
 * filter away all non characters and store the valid ones.
 * 
 * 
 * ref: https://stackoverflow.com/questions/3463426
 *
 * It is the responsibility of the caller of readaline to free the 
 *     array using free.
 * 
 *************************************************************************/
#include <stdio.h>

size_t readaline(FILE *inputfd, char **dataapp);
