#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "address.h"
#include "dictionary.h"
#include "bit.h"

/*
 * node_t
 *
 * A single node in the linked list, storing one address_t and a pointer to the 
 * next node.
 */
typedef struct node node_t;
struct node {
	address_t *data;
	node_t *next;
};

/*
 * dictionary_t
 *
 * Represents the dictionary as a singly linked list.
 */
struct dictionary {
	node_t *head;
	node_t *tail;
	size_t n;
};

/*
 * createDictionary
 *
 * Reads address data from a CSV file and stores it in a linked list dictionary.
 *
 * Arguments:
 *   FILE *file: file pointer containing CSV address records
 *
 * Returns:
 *   dictionary_t *: pointer to the created dictionary
 */
dictionary_t *createDictionary(FILE *file) {
	assert(file);

	dictionary_t *dict = malloc(sizeof(dictionary_t));
	assert(dict);
	dict->head = NULL;
	dict->tail = NULL;
	dict->n = 0;

	skipHeader(file);
	char line[MAX_LINE_LEN];

	while (fgets(line, sizeof(line), file)) {
		address_t *address = parseAddress(line); // Parse address from CSV line
		assert(address);
		dictionaryAppend(dict, address); // Add line to dictionary
	}

	return dict;
}

/*
 * dictionaryAppend
 *
 * Appends an address to the end of the dictionary linked list.
 *
 * Arguments:
 *   dictionary_t *dict — the dictionary to append to
 *   address_t *data — the address to add
 */
void dictionaryAppend(dictionary_t *dict, address_t *data) {
	assert(dict);
	assert(data);

	node_t *newNode = malloc(sizeof(node_t));
	assert(newNode);

	newNode->data = data;
	newNode->next = NULL;

	if (dict->head == NULL) {
		// Node is first element and both tail and head need to be updated
		dict->head = newNode;
		dict->tail = newNode;
	} else {
		// Node is added to end of existing list
		dict->tail->next = newNode;
		dict->tail = newNode;
	}

	dict->n++;
}

/*
 * printDictionary
 *
 * Prints all addresses in the dictionary to the given output stream.
 *
 * Arguments:
 *   dictionary_t *dict — the dictionary to print
 *   FILE *output — the output stream 
 */
void printDictionary(dictionary_t *dict, FILE *output) {
	assert(dict);

	node_t *current = dict->head;
	while (current) {
		printAddress(current->data, output);
		printf("\n");
		current = current->next;
	}
}

/*
 * freeDictionary
 *
 * Frees all memory used by the dictionary and its contents.
 *
 * Arguments:
 *   dictionary_t *dict — the dictionary to free
 */
void freeDictionary(dictionary_t *dict) {
	assert(dict);

	node_t *current = dict->head;
	while (current) {
		node_t *next = current->next;
		freeAddress(current->data);
		free(current);
		current = next;
	}

	free(dict);
}

/*
 * searchDictionary
 *
 * Searches for matching addresses using bit-level comparison of EZI_ADD fields.
 * Matches are printed to the output stream. Comparison statistics are printed 
 * to stdout.
 *
 * Arguments:
 *   dictionary_t *dict — the dictionary to search
 *   char *address — the address string to search for
 *   FILE *output — the stream to write matching records to
 */
void searchDictionary(dictionary_t *dict, char *address, FILE *output) {
	assert(dict);
	assert(address);
	assert(output);

	int recordsFound = 0;      
	int bitComparisons = 0;    
	int stringComparisons = 0;
	int nodeComparisons = 0;   

	node_t *current = dict->head;

	fprintf(output, "%s\n", address);

	while (current != NULL) {
		if (bitCompare(getEZI_ADD(current->data), address, &bitComparisons)) {
			// Dictionary key matches address
			recordsFound++;
			printAddress(current->data, output);
		}

		stringComparisons++;    
		nodeComparisons++;     
		current = current->next;
	}

	if (recordsFound == 0) {
		fprintf(output, "--> NOTFOUND\n");
	}

	fprintf(stdout, "%s --> %d records found - comparisons: b%d n%d s%d\n",
	        address, recordsFound, bitComparisons, nodeComparisons, 
			stringComparisons);
}