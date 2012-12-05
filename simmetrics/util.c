/*
 * util.c
 *
 *  Created on: 29 Nov 2012
 *      Author: johnathan
 */

#include <string.h>
#include <stdbool.h>
#include "util.h"

unsigned int str_hash(const char *s) {

    unsigned int hash = 0;
    int c;

    while((c = *s++))
    {
        /* hash = hash * 33 ^ c */
        hash = ((hash << 5) + hash) ^ c;
    }

    return hash;

}

