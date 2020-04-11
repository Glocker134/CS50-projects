// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

#define HASHTABLE 100

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// Ideally, the size of a hash table should be 1.3 times the maximum number of keys that
// Will be in the table, and it should also be a prime number.
// Source: http://cseweb.ucsd.edu/~kube/cls/100/Lectures/lec16/lec16-8.html
// The large dictionary has 143091 entries. 1.3 times is 186018, which is not a prime.
// The closest prime is 186019, which will be the maximum number of buckets in the hash table.
const unsigned int N = 186019;

// Hash table
node *table[N];

// Dictionary size - it's updated as new words are added to it via load
unsigned int dictionary_size = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *helper = table[hash(word)];
    while (helper != NULL)
    {
        if (strcasecmp(word, helper->word) == 0)
        {
            return true;
        }
        helper = helper->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // djb2 hash function by Daniel J. Bernstein. Case-insensitive.
    // Source: http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char str[LENGTH + 1];
    while (fscanf(file, "%s", str) != EOF)
    {
        int index = hash(str);
        node *item = malloc(sizeof(node));
        strcpy(item->word, str);
        item->next = table[index];
        table[index] = item;
        dictionary_size++;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *check = table[i];
        while (check != NULL)
        {
            node *tmp = check;
            check = check->next;
            free(tmp);
        }
    }
    return true;
}


