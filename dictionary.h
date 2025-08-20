#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

typedef struct dictionary dictionary_t;

dictionary_t *createDictionary(FILE *file);
void dictionaryAppend(dictionary_t *dict, address_t *data);
void printDictionary(dictionary_t *dict, FILE *output);
void freeDictionary(dictionary_t *dict);
void searchDictionary(dictionary_t *dict, char *address, FILE* output);

#endif