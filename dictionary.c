/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"

/**
 * dictionary data structure: it's worth a trie
 */
#define KIDS 27

typedef struct node
{
    bool is_word;
    struct node* children[KIDS]
}
node;

// initialize root node
node* root;
root = (node *)malloc(sizeof(node));
// check for NULL
if (root == NULL)
{
    printf("Could not allocate memory to create root node\n");
    exit(1);
}
// set children to NULL
for (i = 0; i < KIDS; i++)
{
    root->children[i] = NULL;
}

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
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
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
