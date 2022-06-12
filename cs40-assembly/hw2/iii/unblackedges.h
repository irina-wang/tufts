/*****************************************
 * 
 * unblackedges.h
 * 
 * 
 * Authors    : Tianyi Ma -- tma02
 *              Mengqi Irina Wang -- mwang17 
 * Date       : 2019/09/19
 *
 *****************************************/

#ifndef UNBLACKEDGES_INCLUDED
#define UNBLACKEDGES_INCLUDED

#include <stdio.h>
#include "bit2.h"
#include "list.h"
#include "stdbool.h"

FILE* get_file(int, char **);
Bit2_T pbm_read(FILE *);
void read_in(int, int, Bit2_T, int, void *);
void remove_edge(Bit2_T);
void modify_img(int, int, Bit2_T, int, void *);
bool check_neighbor(Bit2_T, int, int);
void scan_img(Bit2_T, Bit2_T, int, int);
void pbm_write(FILE *, Bit2_T);

#endif
