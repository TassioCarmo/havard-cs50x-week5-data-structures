// Implements a dictionary's functionality

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int TABLE_BUCKETS = 99;
unsigned int word_count;
unsigned int hash_value;

// Hash table
node *table[TABLE_BUCKETS];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    hash_value = hash(word);
    node *cursor = table[hash_value];

    while (cursor != 0)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long total = 0;

    for (int i = 0, word_size = strlen(word); i < word_size; i++)
    {
        total += tolower(word[i]);
    }

    return total % TABLE_BUCKETS;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Opens the FILE and read it
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "There has been an error");
        return false;
    }

    //array of the words.
    char list[LENGTH + 1];

    while (fscanf(file, "%s", list) != EOF)
    {
        word_count++;
        //allocate memory for each new node created.
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return 1;
        }

        strcpy(new_node->word, list);
        new_node->next = NULL;

        int i = hash(list);

        if (table[i] == NULL)
        {
            table[i] = new_node;
        }
        else
        {
            new_node->next = table[i];
            table[i] = new_node;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //if the number of words is greater than 0 returns it
    if (word_count > 0)
    {
        return word_count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //makes a cursor which points to the head node. that'll go through the linked lists freeing the memory.
    node *tmp = NULL;
    node *cursor = NULL;
    for (int i = 0; i < TABLE_BUCKETS; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}


