#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "address.h"
#include "dictionary.h"
#include "bit.h"

/*
 * parseAddress
 *
 * Parses a single line of CSV input, splitting fields by comma.
 * Populates a temporary 2D array of strings and passes it to createAddress.
 */
address_t *parseAddress(char *line) {
    assert(line);

    char fields[MAX_FIELDS][MAX_FIELD_LEN];
    int stringIndex = 0;
    int fieldIndex = 0;
    int c;

    for (int i = 0; line[i] != '\0'; i++) {
        c = line[i];

        if (c == ',' || c == '\n') {
            // End of field
            fields[fieldIndex][stringIndex] = '\0'; // Add null byte character
            fieldIndex++; // Move to next field
            stringIndex = 0; // Reset string length
            if (c == '\n') break; // End of address input
        } else {
            if (stringIndex < MAX_FIELD_LEN - 1)
                // Add character to field
                fields[fieldIndex][stringIndex++] = (char)c; 
        }
    }

    return createAddress(fields);
}


/*
 * skipHeader
 *
 * Advances the file pointer past the header line (assumes one line).
 */
void skipHeader(FILE *file) {
    while (fgetc(file) != '\n') {
        // skip all characters until next line
    }
}


/*
 * createAddress
 *
 * Dynamically allocates and fills an address_t struct
 * using data from the parsed field array.
 */
address_t *createAddress(char fields[MAX_FIELDS][MAX_FIELD_LEN]) {
    address_t *address = malloc(sizeof(address_t));
    assert(address);

    address->PFI = fieldCopy(fields[0]);
    address->EZI_ADD = fieldCopy(fields[1]);
    address->SRC_VERIF = fieldCopy(fields[2]);
    address->PROPSTATUS = fieldCopy(fields[3]);
    address->GCODEFEAT = fieldCopy(fields[4]);
    address->LOC_DESC = fieldCopy(fields[5]);
    address->BLGUNTTYP = fieldCopy(fields[6]);
    address->HSAUNITID = fieldCopy(fields[7]);
    address->BUNIT_PRE1 = fieldCopy(fields[8]);
    address->BUNIT_ID1 = fieldCopy(fields[9]);
    address->BUNIT_SUF1 = fieldCopy(fields[10]);
    address->BUNIT_PRE2 = fieldCopy(fields[11]);
    address->BUNIT_ID2 = fieldCopy(fields[12]);
    address->BUNIT_SUF2 = fieldCopy(fields[13]);
    address->FLOOR_TYPE = fieldCopy(fields[14]);
    address->FLOOR_NO_1 = fieldCopy(fields[15]);
    address->FLOOR_NO_2 = fieldCopy(fields[16]);
    address->BUILDING = fieldCopy(fields[17]);
    address->COMPLEX = fieldCopy(fields[18]);
    address->HSE_PREF1 = fieldCopy(fields[19]);
    address->HSE_NUM1 = fieldCopy(fields[20]);
    address->HSE_SUF1 = fieldCopy(fields[21]);
    address->HSE_PREF2 = fieldCopy(fields[22]);
    address->HSE_NUM2 = fieldCopy(fields[23]);
    address->HSE_SUF2 = fieldCopy(fields[24]);
    address->DISP_NUM1 = fieldCopy(fields[25]);
    address->ROAD_NAME = fieldCopy(fields[26]);
    address->ROAD_TYPE = fieldCopy(fields[27]);
    address->RD_SUF = fieldCopy(fields[28]);
    address->LOCALITY = fieldCopy(fields[29]);
    address->STATE = fieldCopy(fields[30]);
    address->POSTCODE = fieldCopy(fields[31]);
    address->ACCESSTYPE = fieldCopy(fields[32]);
    address->x = fieldCopy(fields[33]);
    address->y = fieldCopy(fields[34]);

    return address;
}


/*
 * fieldCopy
 *
 * Returns a heap-allocated copy of a field.
 * Guarantees non-null pointer, even for empty strings.
 */
char *fieldCopy(char *string) {
    assert(string);
    char *copy;

    if (string[0] == '\0') {
        // String is empty
        copy = strdup("");
    } else {
        // String is not empty
        copy = strdup(string);
    }

    assert(copy);
    return copy;
}


/*
 * printAddress
 *
 * Outputs all fields of the given address in a consistent format.
 * Used for display or writing to output file.
 */
void printAddress(address_t *address, FILE *output) {
    assert(address);

    fprintf(output, "--> EZI_ADD: %s || ", address->EZI_ADD);
    fprintf(output, "PFI: %s || ", address->PFI);
    fprintf(output, "SRC_VERIF: %s || ", address->SRC_VERIF);
    fprintf(output, "PROPSTATUS: %s || ", address->PROPSTATUS);
    fprintf(output, "GCODEFEAT: %s || ", address->GCODEFEAT);
    fprintf(output, "LOC_DESC: %s || ", address->LOC_DESC);
    fprintf(output, "BLGUNTTYP: %s || ", address->BLGUNTTYP);
    fprintf(output, "HSAUNITID: %s || ", address->HSAUNITID);
    fprintf(output, "BUNIT_PRE1: %s || ", address->BUNIT_PRE1);
    fprintf(output, "BUNIT_ID1: %s || ", address->BUNIT_ID1);
    fprintf(output, "BUNIT_SUF1: %s || ", address->BUNIT_SUF1);
    fprintf(output, "BUNIT_PRE2: %s || ", address->BUNIT_PRE2);
    fprintf(output, "BUNIT_ID2: %s || ", address->BUNIT_ID2);
    fprintf(output, "BUNIT_SUF2: %s || ", address->BUNIT_SUF2);
    fprintf(output, "FLOOR_TYPE: %s || ", address->FLOOR_TYPE);
    fprintf(output, "FLOOR_NO_1: %s || ", address->FLOOR_NO_1);
    fprintf(output, "FLOOR_NO_2: %s || ", address->FLOOR_NO_2);
    fprintf(output, "BUILDING: %s || ", address->BUILDING);
    fprintf(output, "COMPLEX: %s || ", address->COMPLEX);
    fprintf(output, "HSE_PREF1: %s || ", address->HSE_PREF1);
    fprintf(output, "HSE_NUM1: %s || ", address->HSE_NUM1);
    fprintf(output, "HSE_SUF1: %s || ", address->HSE_SUF1);
    fprintf(output, "HSE_PREF2: %s || ", address->HSE_PREF2);
    fprintf(output, "HSE_NUM2: %s || ", address->HSE_NUM2);
    fprintf(output, "HSE_SUF2: %s || ", address->HSE_SUF2);
    fprintf(output, "DISP_NUM1: %s || ", address->DISP_NUM1);
    fprintf(output, "ROAD_NAME: %s || ", address->ROAD_NAME);
    fprintf(output, "ROAD_TYPE: %s || ", address->ROAD_TYPE);
    fprintf(output, "RD_SUF: %s || ", address->RD_SUF);
    fprintf(output, "LOCALITY: %s || ", address->LOCALITY);
    fprintf(output, "STATE: %s || ", address->STATE);
    fprintf(output, "POSTCODE: %s || ", address->POSTCODE);
    fprintf(output, "ACCESSTYPE: %s || ", address->ACCESSTYPE);
    fprintf(output, "x: %s || ", address->x);
    fprintf(output, "y: %s\n", address->y);
}


/*
 * freeAddress
 *
 * Frees all memory associated with a single address_t struct,
 * including all individual string fields.
 */
void freeAddress(address_t *address) {
    assert(address);

    free(address->PFI);
    free(address->EZI_ADD);
    free(address->SRC_VERIF);
    free(address->PROPSTATUS);
    free(address->GCODEFEAT);
    free(address->LOC_DESC);
    free(address->BLGUNTTYP);
    free(address->HSAUNITID);
    free(address->BUNIT_PRE1);
    free(address->BUNIT_ID1);
    free(address->BUNIT_SUF1);
    free(address->BUNIT_PRE2);
    free(address->BUNIT_ID2);
    free(address->BUNIT_SUF2);
    free(address->FLOOR_TYPE);
    free(address->FLOOR_NO_1);
    free(address->FLOOR_NO_2);
    free(address->BUILDING);
    free(address->COMPLEX);
    free(address->HSE_PREF1);
    free(address->HSE_NUM1);
    free(address->HSE_SUF1);
    free(address->HSE_PREF2);
    free(address->HSE_NUM2);
    free(address->HSE_SUF2);
    free(address->DISP_NUM1);
    free(address->ROAD_NAME);
    free(address->ROAD_TYPE);
    free(address->RD_SUF);
    free(address->LOCALITY);
    free(address->STATE);
    free(address->POSTCODE);
    free(address->ACCESSTYPE);
    free(address->x);
    free(address->y);
    free(address);
}

/*
 * getEZI_ADD
 *
 * Returns the EZI_ADD field from an address.
 */
char *getEZI_ADD(address_t *address) {
    assert(address);
    return address->EZI_ADD;
}
