// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Defining method to free nodes
void freeNodes(struct node *startNode);

// TODO: Choose number of buckets in hash table
const unsigned int N = LENGTH * 'Z' - 'A';

// Hash table
node *table[N];

int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int location = hash(word);
    node *currentNode = table[location];
    while (currentNode != NULL)
    {
        if (strcasecmp(currentNode->word, word) == 0)
        {
            return true;
        }
        currentNode = currentNode->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hash = 0;
    for (int i = 0; word[i] != '\n' && word[i] != '\0'; i++)
    {
        hash += toupper(word[i]);
    }
    return hash >= 'A' ? hash - 'A' : hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    bool loaded = false;
    if (file != NULL)
    {
        char word[LENGTH + 1];
        while (fgets(word, LENGTH + 2, file))
        {
            int location = hash(word);
            node *currentNode = table[location];
            if (currentNode == NULL)
            {
                currentNode = malloc(sizeof(node));
                currentNode->next = NULL; // To shut up valgrind
                copy(currentNode->word, word);
                table[location] = currentNode;
            }
            else
            {
                while (currentNode->next != NULL)
                {
                    currentNode = currentNode->next;
                }
                currentNode->next = malloc(sizeof(node));
                currentNode->next->next = NULL; // To shut up valgrind
                copy(currentNode->next->word, word);
            }
            count++;
        }
        loaded = true;
    }
    fclose(file);
    return loaded;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            freeNodes(table[i]);
        }
        table[i] = NULL;
    }
    count = 0;
    return true;
}

void freeNodes(struct node *startNode)
{
    if (startNode->next != NULL)
    {
        freeNodes(startNode->next);
    }
    free(startNode);
}

void copy(char *destination, char *source)
{
    int i;
    for (i = 0; source[i] != '\n' && source[i] != '\0'; i++)
    {
        destination[i] = source[i];
    }
    for (; i < LENGTH + 1; i++)
    {
        destination[i] = '\0';
    }
}
