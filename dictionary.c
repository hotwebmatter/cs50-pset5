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

    // locally-scoped variable declarations
    int charpos = -1; // initially set out of range
    node* curr = root;

    for (int c = fgetc(fp); c!= EOF; c = fgetc(fp))
    {
        if (c == '\n')
        {
            curr->is_word = true;
            wordcount++;
            curr = root;
        }
        else if (c == '\'')
        {
            charpos = 26;
            curr->children[charpos] = (node *)malloc(sizeof(node));
            curr = curr->children[charpos];
        }
        else
        {
            charpos = toupper(c) - 'A';
            curr->children[charpos] = (node *)malloc(sizeof(node));
            curr = curr->children[charpos];
        }
        // printf("character: %c\tcharpos: %i\n", c, charpos);
    }
    // printf("word count: %i\n", wordcount);
    // return false;
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordcount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    bool result = free_trie(root);
    return result;
}

bool free_trie(node* curr)
{
    bool result = false;
    for (int i = 0; i < KIDS; i++)
    {
        if (curr->children[i])
        {
            result = free_trie(curr->children[i]);
        }
        else
        {
            free(curr);
            return true;
        }
    }
    return result;
}
