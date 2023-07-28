// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
short int numWords = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int i = hash(word);

    node *n = table[i];

    while (n != NULL)
    {
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }
        else
        {
            n = n->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hash = 0, c;

    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = ((hash << 5) + hash) * word[i];
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        printf("El diccionario no pudo abrirse\n");
        return 1;
    }

    char buffer[LENGTH + 1];

    while (fscanf(file, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return 1;
        }

        strcpy(n->word, buffer);
        n->next = NULL;

        int i = hash(buffer);

        if (table[i] != NULL)
        {
            n->next = table[i];
        }
        table[i] = n;
        numWords++;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return numWords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *n = table[0];

    while (n != NULL)
    {
        node *temp = n;
        n = n->next;
        free(temp);
    }
    return true;
}
