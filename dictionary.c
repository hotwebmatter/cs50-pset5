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

// initialize root node and crawler
node *root, *curr = NULL;

// declare global variable
int wordcount = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // int len = strlen(word);      // without strlen() I no longer need <string.h>
    if (root == NULL)
    {
        printf("Somehow, the dictionary was never loaded into memory.\n");
        exit(1);
    }
    curr = root;
    // for (int i = 0, pos = -1; i < len ; i++)     // the loop below is better!
    for ( ; *word != '\0' ; word++)
    {
        int pos = charPosition(*word);
        if (curr->children[pos] == NULL)
        {
            return false;
        }
        else 
        {
            curr = curr->children[pos];
        }
    }
    if (curr->is_word == true)
    {
        return true;
    }
    else
    {
        return false;
    }
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
    for (int i = 0; i < KIDS; i++)
    {
        root->children[i] = NULL;    // Initialize all pointers
    }

    // try to open dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    // variable declarations
    int charpos = -1; // initially set out of range
    curr = root;

    for (int c = fgetc(fp); c!= EOF; c = fgetc(fp))
    {
        if (c == '\n')
        {
            curr->is_word = true;
            wordcount++;
            curr = root;
        }
        else
        {
            charpos = charPosition(c);
            if (curr->children[charpos] == NULL)
            {
                curr->children[charpos] = (node *)malloc(sizeof(node));
                if (curr->children[charpos] == NULL)
                {
                    printf("Error: Failed to allocate memory for node\n");
                    return false;
                }
                curr->children[charpos]->is_word = false;
                for (int j = 0; j < KIDS; j++)
                {
                    curr->children[j] = NULL;    // Initialize all pointers
                }

            }
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
        if (curr->children[i] != NULL)
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

int charPosition(int character)
{
    if (character == '\'')
        {
            return 26;
        }
        else
        {
            return toupper(character) - 'A';
        }
}
