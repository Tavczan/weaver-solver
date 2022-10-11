#ifndef WORD_LIST_H
#define WORD_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    This should only store functions and structs related to the storage, processing and extraction of words from files
*/

struct word_element {
    char contents[5]; // 4 visible letter string
    struct word_element * next;
};

/* Make a new word_element STRUCT from a pointer to a char, next is set to NULL */
struct word_element * create_word_element(char* word);
/* Makes a new word list (which is just a pointer from its point of view), for readability purposes */
struct word_element * create_new_word_list();
/* Appends a new word at the end of the list. Returns the new list head if it was changed */
struct word_element * append_word_list(struct word_element *list, struct word_element *word);
/* Returns an integer value length of a list */
int word_list_length(struct word_element *list);
/* Returns a list of 4 letter words from file */
struct word_element * make_list_from_file(const char *filename);
/* Prints a word list, duh */
void print_word_list(struct word_element *list);
/* Removes a list from memory, returns a NULL pointer so you don't leave a hanging pointer you moron*/
struct word_element * free_word_list(struct word_element *list);
/* Makes a numbered table from a list */
char (*tablearize_word_list(struct word_element *list))[5];
/* Returns a node ID by searching for a string*/
int get_node_id_by_string(char (*words)[5], int length, char *seek);

#endif