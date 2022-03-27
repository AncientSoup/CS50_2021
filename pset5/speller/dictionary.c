// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = (LENGTH * 'z');

// Total words loaded from dictionary.
int total = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int num = hash(word);
    
    node *cursor = table[num];
    
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int length = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        length += tolower(word[i]);
    }
    return (length % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    char word[LENGTH + 1];
    
    if (file == NULL)
    {
        return false;
    }
    
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        
        if (n == NULL)
        {
            return false;
        }
        
        strcpy(n->word, word);
        n->next = NULL;
        
        int index = hash(word);
    
        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
        
        total++;
    }
    
    fclose(file);
    
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return total;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *p = table[i];
        
        while (p != NULL)
        {
            node *d = p;
            p = p->next;
            free(d);
        }
        
        table[i] = NULL;
    }
    return true;
}