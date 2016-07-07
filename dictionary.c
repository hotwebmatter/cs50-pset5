/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <string.h>
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
    int len = strlen(word);
    if (root == NULL)
    {
        printf("Somehow, the dictionary was never loaded into memory.\n");
        exit(1);
    }
    curr = root;
    for (int i = 0, pos = -1; i < len ; i++)
    {
        pos = charPosition(word[i]);
        if (curr->children[pos] == NULL)
        {
            return false;
        }
        else 
        {
            curr = curr->children[pos];
        }
        if (i == len - 1 && curr->is_word == true)
        {
            return true;
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
            curr->children[charpos] = (node *)malloc(sizeof(node));
            if (curr->children[charpos] == NULL)
            {
                printf("Error: Failed to allocate memory for node\n");
                return false;
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
    // bool result = false;
    
    // recursive case
    for (int i = 0; i < KIDS; i++)
    {
        if (curr->children[i] != NULL)
        {
            // result = free_trie(curr->children[i]);
            free_trie(curr->children[i]);
        }
    }
    // base case
    free(curr);
    return true;
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
