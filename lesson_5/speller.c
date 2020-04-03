// Implements a dictionary's functionality

#include <stdbool.h>

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

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char *aux = strdup(word);

    // Changing aux to lowercase
    char *lower = aux;
    while(*lower)
    {
        *lower = tolower(*lower);
        lower++;
    }

    for (node *helper = table[hash(word)]; helper != NULL; helper = helper->next)
    {
        if (strcmp(aux, helper->word) == 0)
        {
            return true;
        }
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
    // TODO
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
