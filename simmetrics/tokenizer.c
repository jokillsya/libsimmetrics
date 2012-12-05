/*
 * tokenizer.c
 *
 *  Created on: 05 Dec 2012
 *      Author: johnathan
 */

#include <stddef.h>
#include "cost.h"
#include "uthash.h"
#include "tokenizer.h"

static unsigned int str_hash(const char *s) {

    unsigned int hash = 0;
    int c;

    while((c = *s++))
    {
        /* hash = hash * 33 ^ c */
        hash = ((hash << 5) + hash) ^ c;
    }

    return hash;

}

tokenizer_t *uq_tokenize_hash(const char *str, const char *delimiters) {

	unsigned int hash;
	tokenizer_t *s, *table = NULL;
	char *tok;
	char tmp[strlen(str) + 1];
	strcpy(tmp, str);

	tok = strtok(tmp, delimiters);

	while(tok != NULL) {

		hash = str_hash(tok);

		HASH_FIND_INT(table, &hash, s);

		if(s == NULL) {

			s = malloc(sizeof(tokenizer_t));
			s->key = str_hash(tok);
			s->value = malloc(sizeof(char) * (strlen(tok) + 1));
			strcpy(s->value, tok);
			HASH_ADD_INT(table, key, s);

		}

		tok = strtok(NULL, delimiters);

	}

	return table;

}

void tokenizer_free(tokenizer_t *table) {

	tokenizer_t *s, *tmp;

	HASH_ITER(hh, table, s, tmp) {

		HASH_DEL(table, s);
		free(s->value);
		free(s);

	}

}


