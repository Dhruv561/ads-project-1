/* Number of bits in a single character. */
#ifndef _BIT_H_
#define _BIT_H_
#include <stdio.h>
#include "address.h"

#define BITS_PER_BYTE 8

int getBit(char *s, unsigned int bitIndex);
int bitCompare(char *s1, char *s2, int *totalComparisons);

#endif
