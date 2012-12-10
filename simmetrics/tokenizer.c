/*
 * tokenizer.c
 *
 *  Created on: 05 Dec 2012
 *      Author: johnathan
 */

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "cost.h"
#include "uthash.h"
#include "utlist.h"
#include "utarray.h"
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

dl_token_t *tokenize_to_dllist(const char *str, const char *delimiters) {

	dl_token_t *el;
	dl_token_t *r = NULL;

	char *tok;
	char tmp[strlen(str) + 1];
	strcpy(tmp, str);

	tok = strtok(tmp, delimiters);

	while(tok != NULL) {

		el = (dl_token_t *)malloc(sizeof(dl_token_t));
		el->token = strdup(tok);
		DL_APPEND(r, el);
		tok = strtok(NULL, delimiters);

	}

	return r;

}

hash_token_t *uq_tokenize_to_hash(const char *str, const char *delimiters) {

	unsigned int hash;
	hash_token_t *s, *table = NULL;
	char *tok;
	char tmp[strlen(str) + 1];
	strcpy(tmp, str);

	tok = strtok(tmp, delimiters);

	while(tok != NULL) {

		hash = str_hash(tok);

		HASH_FIND_INT(table, &hash, s);

		if(s == NULL) {

			s = malloc(sizeof(hash_token_t));
			s->key = str_hash(tok);
			s->value = strdup(tok);
			HASH_ADD_INT(table, key, s);

		}

		tok = strtok(NULL, delimiters);

	}

	return table;

}

hash_token_t *merge_tokens(hash_token_t *t1, hash_token_t *t2) {

	hash_token_t *res = NULL, *s, *tmp;

	for(s = t1; s != NULL; s = s->hh.next) {

		HASH_FIND_INT(res, &s->key, tmp);

		if(tmp == NULL) {

			tmp = malloc(sizeof(hash_token_t));
			tmp->key = s->key;
			tmp->value = strdup(s->value);
			HASH_ADD_INT(res, key, tmp);

		}

	}

	for(s = t2; s != NULL; s = s->hh.next) {

		HASH_FIND_INT(res, &s->key, tmp);

		if(tmp == NULL) {

			tmp = malloc(sizeof(hash_token_t));
			tmp->key = s->key;
			tmp->value = strdup(s->value);
			HASH_ADD_INT(res, key, tmp);

		}

	}

	return res;

}

UT_array *tokenize_to_utarray(const char *str, const char *delimiters) {

	UT_array *strs;

	char *tok;
	char tmp[strlen(str) + 1];
	strcpy(tmp, str);

	utarray_new(strs, &ut_str_icd);

	tok = strtok(tmp, delimiters);

	while(tok != NULL) {

		utarray_push_back(strs, &tok);
		tok = strtok(NULL, delimiters);

	}

	return strs;

}

void hash_token_free(hash_token_t *table) {

	hash_token_t *s, *tmp;

	HASH_ITER(hh, table, s, tmp) {

		HASH_DEL(table, s);
		free(s->value);
		free(s);

	}

}

void dll_token_free(dl_token_t *head) {

	dl_token_t *elt, *tmp;

	DL_FOREACH_SAFE(head, elt, tmp) {
		LL_DELETE(head, elt);
		free(elt->token);
		free(elt);
	}

}


