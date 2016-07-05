/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

/**
 * dictionary data structure: it's worth a trie
 */
#define KIDS 27

typedef struct node
{
    bool is_word;
    struct node* children[KIDS];
}
node;

// initialize root node
node* root;

// declare global variables
int wordcount = 0;
int* wcp = &wordcount;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // initialize trie
    root = (node *)malloc(sizeof(node));
    // check for NULL
    if (root == NULL)
    {
        printf("Could not allocate memory to create root node\n");
        exit(1);
    }
    // set is_word to false, children to NULL
    root->is_word = false;
    // for (i = 0; i < KIDS; i++)
    // {
    //     root->children[i] = NULL;
    // }

    // try to open dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    for (int charpos = -1, c = fgetc(fp); c!= EOF; c = fgetc(fp))
    {
        if (c == '\'')
        {
            charpos = 26;
        }
        else
        {
            charpos = toupper(c) - 'A';
        }
        printf("character: %c\tcharpos: %i\n", c, charpos);
    }
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
