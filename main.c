/* Created by Dhruv Verma (dvverma@student.unimelb.edu.au) and 
 * Agamjot Sandhu (agamjot.sandhu@student.unimelb.edu.au)
 * Date: 20/08/2025
 *
 * Reads address data from a file into a linked-list dictionary structure.
 * Then reads search keys (EZI_ADD strings) from standard input, and performs
 * bitwise matching against the dictionary. Results are printed to an output 
 * file, and a summary of comparisons is printed to stdout.
 *
 * Usage:
 *   ./stage1_search 1 address_file.txt output_file.txt
 *
 * Command-line arguments:
 *   stage_number: currently must be "1"
 *   address_file: path to the input address file (CSV)
 *   output_file:  path to write the results
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "address.h"
#include "dictionary.h"
#include "bit.h"

#define EXIT_FAILURE 1


void stage1(FILE *input, FILE *output);

int main(int argc, char *argv[]) {
    // check argument count 
    if (argc < 4) {
        fprintf(stderr, 
            "Usage: %s <stage_number> <address_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open input and output files 
    FILE *input = fopen(argv[2], "r");
    assert(input);  
    FILE *output = fopen(argv[3], "w");
    assert(output);  

    // Run Stage 1 logic if specified 
    if (atoi(argv[1]) == 1) {
        stage1(input, output);
    }

    // clean-up
    fclose(input);
    fclose(output);

    return 0;
}

/*
 * stage1
 *
 * Reads the address file into a dictionary (linked list).
 * Then reads one EZI_ADD per line from stdin and searches for matches.
 * Matching records are printed to output; summary goes to stdout.
 *
 * Parameters:
 *   FILE *input: file stream containing address data
 *   FILE *output: file stream to write search results
 */
void stage1(FILE *input, FILE *output) {
    // Build dictionary from address input 
    dictionary_t *dict = createDictionary(input);

    // Buffer to store user-entered EZI_ADDs 
    char EZI_ADD[MAX_FIELD_LEN + 1];

    // Read one line at a time from stdin and search 
    while (scanf(" %[^\n]", EZI_ADD) == 1) {
        searchDictionary(dict, EZI_ADD, output);
    }

    // Free memory after use 
    freeDictionary(dict);
}
