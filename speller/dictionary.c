// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 70000;

// Hash table
node *table[N];

// Count of words from dictionary loaded into hash table
unsigned int words_dict = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *cursor = NULL;
    char low_word[LENGTH + 1];
    int i = 0;

    // Lower case the word to hash
    for (; word[i] != '\0'; i++)
    {
        low_word[i] = tolower(word[i]);
    }
    low_word[i] = '\0';

    // Hash the lower case word
    int hash_index = hash(low_word);
    if (hash_index >= N || hash_index < 0)
    {
        printf("Check error: Invalid hash code generated for %s.\n", word);
        return false;
    }

    // check if word (lowered case) is present in dictionary (which contains lower case words)
    cursor = table[hash_index];
    while (cursor != NULL)
    {
        if (strcmp(cursor->word, low_word) == 0)
        {
            // word is in dictionary
            return true;
        }
        cursor = cursor->next;
    }
    // word is not in dictionary
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    // Apply hash function on word
    // Source 1: https://www.youtube.com/watch?v=jtMwp0FqEcg
    // Source 2: https://computinglife.wordpress.com/2008/11/20/why-do-hash-functions-use-prime-numbers/
    int hash_index = 7;
    for (int i = 0; i < strlen(word); i++)
    {
        hash_index = hash_index * 31 + word[i];
    }

    if (hash_index == 7)
    {
        printf("Hash error: Did not enter the hash function loop\n");
        return N;
    }

    // Else return generated deterministic hash index
    return hash_index % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    int hash_index = N;
    char load_word[LENGTH + 1];

    // Initialize hash table with null pointers
    // This is to ensure random values don't get picked up
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open dictionary file
    FILE *dict_ptr = fopen(dictionary, "r");
    if (dict_ptr == NULL)
    {
        printf("Load error: Cannot open dictionary file.\n");
        return false;
    }

    // Read strings from dictionary one at a time
    while (fscanf(dict_ptr, "%s", load_word) != EOF)
    {
        // Create a new node for each word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Load error: Cannot create new node.\n");
            unload();
            return false;
        }
        strcpy(new_node->word, load_word);
        new_node->next = NULL;

        // Hash word to obtain an index position in hash table
        hash_index = hash(load_word);

        if (hash_index >= N || hash_index < 0)
        {
            printf("Load error: Invalid hash code generated for %s.\n", load_word);
            unload();
            return false;
        }

        // Valid hash index generated
        // Load word (new_node) into this index position in hash table
        if (table[hash_index] == NULL)
        {
            // first word in this index location, point directly to new node
            table[hash_index] = new_node;
        }
        else
        {
            // a word exists in this index location, add as head of linked list
            new_node->next = table[hash_index];
            table[hash_index] = new_node;
        }
        words_dict++;
    }

    // Check if there was an error
    if (ferror(dict_ptr))
    {
        fclose(dict_ptr);
        printf("Load error: Cannot open dictionary as file\n");
        return false;
    }

    // Close dictionary file
    fclose(dict_ptr);

    // Loaded dictionary successfully
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Counted during loading dictionary
    return words_dict;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Free memory that was dynamically allocated for hash table
    node *cursor = NULL;
    node *tmp = NULL;

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        tmp = table[i];
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }

    // Unload successful
    return true;
    // run valgrind to test for memory leaks
}
