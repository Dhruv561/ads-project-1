#ifndef _ADDRESS_H_
#define _ADDRESS_H_

#include <stdio.h>

// Constants for parsing address data
#define MAX_FIELD_LEN 127     
#define MAX_LINE_LEN 511      
#define MAX_FIELDS 35             

// Represents a full address record with 35+ fields, all as strings
struct address {
    char *PFI;
    char *EZI_ADD;
    char *SRC_VERIF;
    char *PROPSTATUS;
    char *GCODEFEAT;
    char *LOC_DESC;
    char *BLGUNTTYP;
    char *HSAUNITID;
    char *BUNIT_PRE1;
    char *BUNIT_ID1;
    char *BUNIT_SUF1;
    char *BUNIT_PRE2;
    char *BUNIT_ID2;
    char *BUNIT_SUF2;
    char *FLOOR_TYPE;
    char *FLOOR_NO_1;
    char *FLOOR_NO_2;
    char *BUILDING;
    char *COMPLEX;
    char *HSE_PREF1;
    char *HSE_NUM1;
    char *HSE_SUF1;
    char *HSE_PREF2;
    char *HSE_NUM2;
    char *HSE_SUF2;
    char *DISP_NUM1;
    char *ROAD_NAME;
    char *ROAD_TYPE;
    char *RD_SUF;
    char *LOCALITY;
    char *STATE;
    char *POSTCODE;
    char *ACCESSTYPE;
    char *x;
    char *y;
};
typedef struct address address_t; 

// Parses a CSV line into an address_t object
address_t *parseAddress(char *line);

// Skips the header line in a CSV file
void skipHeader(FILE *file);

// Creates an address_t object from a parsed field array
address_t *createAddress(char fields[MAX_FIELDS][MAX_FIELD_LEN]);

// Allocates a safe copy of a field (handles empty strings)
char *fieldCopy(char *string);

// Prints the full address in formatted form
void printAddress(address_t *address, FILE *output);

// Frees all memory used by an address_t object
void freeAddress(address_t *address);

// Returns the EZI_ADD field from the address (often used as a key)
char *getEZI_ADD(address_t *address);

#endif
