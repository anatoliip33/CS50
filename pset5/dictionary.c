/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "dictionary.h"

// size of hashtable
#define SIZE 143091

// nodes for linked list
typedef struct node
{
	char word[LENGTH+1];
	struct node* next;
}
node;

// create hashtable
node* hashtable[SIZE] = {NULL};

// variable tp count words from dictionary
int words;

// hash function
int hash(char* word)
{
	unsigned int hash = 0;
	for (int i = 0, n = strlen(word); i < n; i++)
	{
		hash = (hash << 2) ^ word[i];
	}
	return hash % SIZE;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // variable to store word
    char temp_word[LENGTH + 1];
    int length = strlen(word);
    
    for (int i = 0; i < length; i++)
    {
    	temp_word[i] = tolower(word[i]);
    }
   	
   	// end of word
   	temp_word[length] = '\0';
   	
   	// index of the array where word will be 
   	int index = hash(temp_word);
   	
   	// if there is no index
   	if (hashtable[index] == NULL)
   	{
   		return false;
   	}
   	
   	// cursor in hashtable to compare words
   	node* cursor = hashtable[index];
   	
   	// compare words in hashtable index
   	while (cursor != NULL)
   	{
   		if (strcmp(temp_word, cursor->word) == 0)
   		{
   			return true;
   		}
   		cursor = cursor->next;
   	}
   	
   	return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary
    FILE* fp = fopen(dictionary, "r");
    
    if (fp == NULL)
    {
    	printf("Could not open %s.\n", dictionary);
    	return false;
    }
    
    // array where word will be stored
    char word[LENGTH+1];
    
    while (fscanf(fp, "%s\n", word)!= EOF)
    {
    	// memory for new word
    	node* new_word = malloc(sizeof(node));
    	
    	// copy word to the new node
    	strcpy(new_word->word, word);
    	
    	// find index of the array where word should stored
    	int index = hash(word);
    	
    	if (hashtable[index] == NULL)
    	{
    		hashtable[index] = new_word;
    		new_word->next = NULL;
    	}
    	else
    	{
    		new_word->next = hashtable[index];
    		hashtable[index] = new_word;
    	}
    	words++;
    }
    
    fclose(fp);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // return count of words in dictionary
    return words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    int index = 0;
    
    while (index < SIZE)
    {
    	// check if hastable with key index not empty
    	if (hashtable[index] == NULL)
    		index++;
    	
    	else
    	{
    		while (hashtable[index] != NULL)
    		{
    			node* cursor = hashtable[index];
    			hashtable[index] = cursor->next;
    			free(cursor);
    		}
    		
    		index++;
    	}
    }
    
    return true;
}
