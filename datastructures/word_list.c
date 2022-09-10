#ifndef WORD_LIST_C
#define WORD_LIST_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word_list.h"

#define MAX_LINE_LENGTH 100

struct word_element * create_word_element(char* word)
{
    struct word_element * new_word = malloc(sizeof(struct word_element));
    strncpy(new_word->contents,word,4);
    new_word->contents[4] = '\0';
    new_word->next = NULL;
    return new_word;
}

struct word_element * create_new_word_list()
{
    return NULL;
}

struct word_element * append_word_list(struct word_element *list, struct word_element *word)
{
    // The list is empty
    if (!list)
        return word;
    struct word_element *pointer = list;

    // Move to the end of the list
    while (pointer->next)
    {
        pointer = pointer->next;
    }

    // Append the element
    pointer->next = word;
    word->next = NULL; // Safety
    return list;
}

int word_list_length(struct word_element *list)
{
    if (!list)
        return 0;
    
    int length = 1;

    struct word_element *pointer = list;
    while (pointer->next)
    {
        pointer = pointer->next;
        length++;
    }

    return length;
}

struct word_element * make_list_from_file(const char *filename)
{
    struct word_element * output_list = create_new_word_list();
    
    FILE *input = fopen(filename, "r");

    char line[MAX_LINE_LENGTH] = {0};

    while (fgets(line, MAX_LINE_LENGTH, input))
    {
        /* Print each line */
        
        if (strlen(line) == 5)
        {
            struct word_element * new_word = create_word_element(line);
            output_list = append_word_list(output_list,new_word);
        }
    }

    fclose(input);

    return output_list;
}

void print_word_list(struct word_element *list)
{
    if (!list)
        return;
    

    struct word_element *pointer = list;
    while (pointer)
    {
        printf("%s\n", pointer->contents);
        pointer = pointer->next;
    }
    return;
}

struct word_element * free_word_list(struct word_element *list)
{
    if (!list)
        return NULL;
    

    struct word_element *pointer = list;
    while (pointer)
    {
        struct word_element *prev = pointer;
        pointer = pointer->next;
        free(prev);
    }
    return NULL;
}

char (*tablearize_word_list(struct word_element *list))[5]
{
    if (!list)
        return NULL;

    int length = word_list_length(list);
    char (*newtable)[5] = malloc(sizeof(char)*5*length);

    struct word_element *pointer = list;
    int i = 0;
    while (pointer)
    {
        strcpy(newtable[i], pointer->contents);
        i++;
        pointer = pointer->next;
    }
    return newtable;
}

// This could be done in 1 line with bsearch but I'm lazy. Returns -1 if not found
int get_node_id_by_string(char (*words)[5], int length, char *seek)
{
    // For every graph node in existence
    for (int i = 0; i < length; i++)
    {   
        if (strcmp(seek,words[i]) == 0) return i;
    }
    return -1;
}

#endif