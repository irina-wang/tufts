/***************************************************************************
 *
 * simlines.c
 * 
 * By Yichen Wei <ywei04> and Mengqi Wang (mwang17)
 * 
 * Summary :
 * 
 * The code beneath is used to extract similar lines after filtering out 
 * non-word characters, and then print the matching groups to standard 
 * output with file name and line number. 
 * 
 *************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <table.h>
#include <string.h>
#include <atom.h>
#include <list.h>
#include <ctype.h>
#include "readaline.h"

/*
 * struct that stores the line's information
 *   - filename and line number
 */
typedef struct {
    char *filename;
    int lineno; 
} Lineloc;

void table_clear_row(const void *key, void **value, void *cl);
void list_clear_entry(void **entry, void *cl);
void process_file(Table_T table, FILE *inputfd, char *filename);
void insert_line(Table_T table, char *line_content, char *filename,
                int lineno);
int format_line(char **line_content, int length);
void print_table(const Table_T table);
FILE *open_file(char *filename);
void list_print_map(void **content, void *cl);


int main(int argc, char *argv[])
{
    /* if zero file entered, argc = 1, for loop will not be execed. */
    Table_T table = Table_new(0, NULL, NULL);
    for (int i = 1; i < argc; i++) {
        FILE *curr_file = open_file(argv[i]);
        process_file(table, curr_file, argv[i]);
        fclose(curr_file);
    }
    
    print_table(table);

    Table_map(table, table_clear_row, NULL);

    Table_free(&table);

    return EXIT_SUCCESS;
}


/*
 * table_clear_row(const void *key, void **value, void *cl)
 * 
 * Parameter : pointer to the key.
 *             pointer to the corresponding value (the List, in this case)
 *             void pointer cl (unused)
 * Purpose   : To free the memory of each row in the table
 * Return    : nothing
 * 
 * Note      : It's called by the main function
 */
void table_clear_row(const void *key, void **value, void *cl)
{
    /* suppress warning */
    (void) cl;
    (void) key;
    
    /* extract list from the table. */
    List_T list = *value;

    /* free the Lineloc struct. */
    List_map(list, list_clear_entry, NULL);

    /* free the list. */
    List_free(&list);

    *value = NULL;
}


/*
 * Helper Function
 * list_clear_entry(void **entry, void *cl)
 * 
 * Parameter : double void pointer to the entry, void pointer cl (unused)
 * Purpose   : To release the memory of the each entry
 * Return    : nothing
 * 
 * Note      : It's called by the table_clear_row function
 */
void list_clear_entry(void **entry, void *cl)
{
    /* suppress warning */
    (void) cl;

    /* free the Lineloc struct */
    free(*entry);
    *entry = NULL;
}


/*
 * print_table(const Table_T table)
 * 
 * Parameter : table, the table to be printed
 * Purpose   : To print the matching groups to standard output
 * Return    : nothing
 * 
 */
void print_table(const Table_T table)
{
    /* convert the table to Array */
    void **arr = Table_toArray(table, NULL);

    bool first_line_printed = false;

    /* odd-numbered cells are keys, even-numbered cells are lists. */
    for (int i = 0; arr[i] != NULL; i += 2) {
        /* get the list first */
        List_T curr_list = arr[i + 1];
        int list_len = List_length(curr_list);

        /* if there's more than one entry in the list, print it out. */
        if (list_len > 1) {
            /* print a new line when it's not the first group */
            if (!first_line_printed){
                first_line_printed = true;
            } else {
                printf("\n");
            }

            /* operate on each entry/key */
            printf("%s\n", (char *) arr[i] ); /* key */

            /* make a copy then reverse. */
            List_T new_list = List_reverse(List_copy(curr_list));
            List_map(new_list, list_print_map, NULL);
            List_free(&new_list);
        }
    }

    free(arr);
}


/*
 * Helper Function
 * list_print_map(void **content, void *cl)
 * 
 * Parameter : void **content, pointer to the content of the list
 *             void *cl, unused.
 * Purpose   : Map to all the matching groups that's supposed to be printed out
 *             and print them out
 * Return    : nothing
 * 
 * Note      : It's called by the print_table function
 */
void list_print_map(void **content, void *cl)
{
    (void) cl;

    Lineloc *curr_loc = (Lineloc *) *content;
    printf("%-20s %7d\n", curr_loc->filename, curr_loc->lineno);
}


/*
 * process_file(Table_T table, FILE *inputfd, char *filename)
 * 
 * Parameter : the table,
 *             inputfd, the file to read from.
 *             filename, the name of the file to store in the db
 * Purpose   : Read in lines, format lines and store lines from any given file
 * Return    : nothing
 */
void process_file(Table_T table, FILE *inputfd, char *filename)
{
    char *curr_line;
    /* count line number from 1 */
    int line_len = 0, line_no = 1;

    /* read in one line at a time. */
    while (line_len = readaline(inputfd, &curr_line), curr_line != NULL) {
        line_len = format_line(&curr_line, line_len);

        /* if line length > 0, we add it to the table. */
        if (line_len > 0) {
            insert_line(table, curr_line, filename, line_no);

            free(curr_line);
            curr_line = NULL;
        }
        line_no ++;
    }
}


/*
 * insert_line(Table_T table, char *line_content, char *filename,
 *              int lineno)
 * 
 * Parameter : the table,
 *             string of line content.
 *             string filename, name of the file.
 *             int lineno, the line number of this line
 * Purpose   : insert lines into the table
 * Return    : nothing
 * 
 * Note      : It's called by the process_file function
 */
void insert_line(Table_T table, char *line_content, char *filename,
                int lineno)
{
    /* if line is empty, do nothing. 
     * strcmp returns 0 when two strings are the same.
     */
    if (strcmp(line_content, "") == 0)
        return;
    
    /* assign line location to the struct */
    Lineloc *location = malloc(sizeof(Lineloc));
    location->filename = filename;
    location->lineno = lineno;

    /* create atom, to be used as keys in the table */
    const char *atom = Atom_string(line_content);
    List_T location_list= Table_get(table, atom);
    /* note: line_content's mem will be reed by process_file */

    if (location_list == NULL) {
        /* if the entry is empty, create a new one. */
        location_list = List_list(location, NULL);
    } else { 
        /* if the entry is not empty, modify the list. */
        location_list = List_push(location_list, location);
    }
    /* put the list back */
    Table_put(table, atom, location_list);
}


/*
 * format_line(char **line_content, int length)
 * 
 * Parameter : A pointer to the string containing the line to be formatted.
 *             length, the length to the string
 * Purpose   : modifies line content to remove non-word and non-numeric chars 
 *                (except '_')
 * Return    : int, line length
 * 
 * Note      : It's called by the process_file function
 */
int format_line(char **line_content, int length)
{
    char *new_line = (char *) malloc(length + 1);
    char *old_line = *line_content;
    
    /* current index for new_line and old_line. */
    int new_index = 0, old_index = 0;

    /* traverse through the old line, updating the new one. */
    while (old_index < length) {
        char curr_char = old_line[old_index];
        if (isalnum(curr_char) || curr_char == '_') {
            new_line[new_index] = old_line[old_index];
            new_index ++;
        } else if (new_index != 0 && new_line[new_index - 1] != ' ') {
            new_line[new_index] = ' ';
            new_index ++;
        }
        old_index ++;
    }

    /* final check: remove the space at the end. */
    if (new_index != 0 && new_line[new_index - 1] == ' ') {
        /* update last char to be \0 */
        new_line[new_index - 1] = '\0';
    } else {
        /* update last char to be \0 */
        new_line[new_index] = '\0';

        new_index ++;
    }

    /* update the length */
    length = new_index;

    /* free the old line */
    free(old_line);
    old_line = NULL;

    /* since the new line supposedly have extra chars allocated, 
       we allocate another new string. */
    *line_content = malloc(length);
    strncpy(*line_content, new_line, length);

    /* free the new line */
    free(new_line);
    new_line = NULL;

    return length;
}


/*
 * *open_file(char *filename)
 * 
 * Parameter : char pointer, filename 
 * Purpose   : opens the file and quit when fails to open
 * Return    : FILE pointer, _file
 * 
 * Note      : It's called by the main function
 */
FILE *open_file(char *filename)
{
    FILE *_file = fopen(filename, "r");

    /* if the file is not opened successfully, quit. */
    assert(_file != NULL);

    /* otherwise, return. */
    return _file;
}
