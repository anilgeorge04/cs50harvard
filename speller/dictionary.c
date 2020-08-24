// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// Words loaded in Hash table
unsigned int word_size = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hash_code = hash(word);
    if (hash_code == N)
    {
        // Could not generate hash code for the word. Exit CHECK function.
        printf("Check error: Cannot generate Hash code for %s\n", word);
        return false;
    }

    // Check for word with cursor node to traverse
    node *cursor = malloc(sizeof(node));
    if (cursor == NULL)
    {
        // Unable to create node. Exit CHECK function.
        printf("Check error: Cannot create new node\n");
        return false;
    }
    cursor->next = table[hash_code]->next;
    while(cursor->next != NULL)
    {
        cursor = cursor->next;
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }

    // Did not find in dictionary
    printf("Check: Not present in Dictionary\n");
    free(cursor);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hash_code = 0;
    // TODO
    return hash_code;

    // Failed to create hash code
    return N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dictionary_ptr = fopen(dictionary, "r");
    if (dictionary_ptr == NULL)
    {
        // Could not open dictionary file. Exit LOAD function.
        printf("Load error: Dictionary file not opening\n");
        return false;
    }

    // Load one word at a time to hash table
    char load_word[LENGTH + 1];
    unsigned int hash_code = 0;
    while(fscanf(dictionary, "%s", load_word) != EOF)
    {
        // Create new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // Unable to create node. Exit LOAD function.
            printf("Load error: Cannot create new node\n");
            return false;
        }
        strcpy(n->word, load_word);
        n->next = NULL;

        // Hash word to load to table
        hash_code = hash(load_word);
        if (hash_code == N)
        {
            // Could not generate hash code for the word. Exit LOAD function.
            printf("Load error: Cannot generate Hash code for %s\n", load_word);
            return false;
        }

        // Insert node in hash code location
        n->next = table[hash_code]->next;
        table[hash_code]->next = n;
        word_size++;
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor = malloc(sizeof(node));
    node *tmp = malloc(sizeof(node));
    if (cursor == NULL || tmp == NULL)
    {
        // Unable to create node. Exit UNLOAD function.
        printf("Unload error: Cannot create traverse node\n");
        return false;
    }

    for (int i = 0; i < N; i++)
    {


        // Unload successful
        free(cursor);
        free(tmp);
        return true;
    }

    free(cursor);
    free(tmp);

    // Could not unload hash table
    return false;
}
