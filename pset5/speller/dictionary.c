#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

static const unsigned int N = 26;

// Hash table
static node *table[N];

// Node for pointing position in hash table
static node *cursor;

int count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
    cursor = table[index]->next;
    while (cursor != NULL)
    {
        int result = strcasecmp(cursor->word, word);
        if (result == 0)
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
    int index = (char)tolower(word[0]) - 'a';
    return index;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Your dictionary text file cannot be opened.\n");
        return false;
    }

    // Initialize a head of linked lists
    for (int i = 0; i < N; i++)
    {
        node *item = malloc(sizeof(node));
        if (item == NULL)
        {
            fprintf(stderr, "Can not allocate memory.\n");
            return false;
        }

        item->next = NULL;
        table[i] = item;
    }

    // Read a file and put a data into linked lists
    char buffer[LENGTH + 1];
    int index = 0;
    while (fscanf(file, "%s", buffer) != EOF)
    {
        node *item = malloc(sizeof(node));
        if (item == NULL)
        {
            fprintf(stderr, "Can not allocate memory.\n");
            return false;
        }

        strcpy(item->word, buffer);

        index = hash(item->word);
        item->next = table[index]->next;
        table[index]->next = item;
        count++;
    }
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
