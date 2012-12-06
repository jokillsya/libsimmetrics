/*
 * block_distance.c
 *
 *  Created on: 05 Dec 2012
 *      Author: johnathan
 */
#include <string.h>
#include <stdlib.h>
#include "cost.h"
#include "utlist.h"
#include "uthash.h"
#include "tokenizer.h"

int block_distance_custom(const char * str1, const char *str2, cost_t *cost) {

	dl_token_t *t1 = tokenize_to_dllist(str1, cost->tok_str);
	dl_token_t *t2 = tokenize_to_dllist(str2, cost->tok_str);

	hash_token_t *h1 = uq_tokenize_to_hash(str1, cost->tok_str);
	hash_token_t *h2 = uq_tokenize_to_hash(str2, cost->tok_str);

	hash_token_t *all = merge_tokens(h1, h2);
	hash_token_t *s;
	dl_token_t *tmp;

	int cs1, cs2, td = 0;

	for(s = all; s != NULL; s = s->hh.next) {

		cs1 = 0;
		cs2 = 0;

		DL_FOREACH(t1, tmp) {

			if(strcmp(tmp->token, s->value) == 0)
				cs1++;

		}

		DL_FOREACH(t2, tmp) {

			if(strcmp(tmp->token, s->value) == 0)
				cs2++;

		}

		if(cs1 > cs2)
			td += (cs1 - cs2);
		else
			td += (cs2 - cs1);

	}

	dll_token_free(t1);
	dll_token_free(t2);

	hash_token_free(h1);
	hash_token_free(h2);
	hash_token_free(all);

	return td;

}

