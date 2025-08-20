#include "bit.h"
#include <assert.h>
#include <string.h>

int getBit(char *s, unsigned int bitIndex){
    assert(s && bitIndex >= 0);
    unsigned int byte = bitIndex / BITS_PER_BYTE;
    unsigned int indexFromLeft = bitIndex % BITS_PER_BYTE;
    /* 
        Since we split from the highest order bit first, the bit we are 
        interested will be the highest order bit, rather than a bit that 
        occurs at the end of the
        number. 
    */
    unsigned int offset = (BITS_PER_BYTE - (indexFromLeft) - 1) % BITS_PER_BYTE;
    unsigned char byteOfInterest = s[byte];
    unsigned int offsetMask = (1 << offset);
    unsigned int maskedByte = (byteOfInterest & offsetMask);
    /*
        The masked byte will still have the bit in its original position, 
        to return either 0 or 1, we need to move the bit to the lowest order 
        bit in the number.
    */
    unsigned int bitOnly = maskedByte >> offset;
    return bitOnly;
}

/*
 * bitCompare
 * 
 * Compares two strings bit-by-bit using getBit.
 * Comparison stops at the end of the shorter string (in bits).
 * 
 * Returns 1 if all bits matched, 0 if a mismatch is found.
 * Updates the totalComparisons counter to reflect how many bits were checked.
 * 
 */
int bitCompare(char *s1, char *s2, int *totalComparisons) {
    assert(s1 && s2 && totalComparisons);

    // Get length of both strings
    int len1 = strlen(s1)+1;
    int len2 = strlen(s2)+1;

    // Convert to total bit lengths
    int bits1 = len1 * BITS_PER_BYTE;
    int bits2 = len2 * BITS_PER_BYTE;

    // Determine how many bits to compare (shortest length)
    int minBits = (bits1 < bits2) ? bits1 : bits2;

    // Compare bits one-by-one (including null terminator)
    for (int i = 0; i < minBits; i++) {
        (*totalComparisons)++;
        if (getBit(s1, i) != getBit(s2, i)) {
            // Bits mismatch
            return 0;
        }
    }
    // All bits match
    return 1;
}