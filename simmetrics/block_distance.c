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
#include "utarray.h"
#include "uthash.h"
#include "tokenizer.h"

int block_distance_custom(const char * str1, const char *str2, cost_t *cost) {

	UT_array *t1 = tokenize_to_utarray(str1, cost->tok_str);
	UT_array *t2 = tokenize_to_utarray(str2, cost->tok_str);

	hash_token_t *h1 = uq_tokenize_to_hash(str1, cost->tok_str);
	hash_token_t *h2 = uq_tokenize_to_hash(str2, cost->tok_str);

	hash_token_t *all = merge_tokens(h1, h2);
	hash_token_t *s;

	char **tmp;

	int cs1, cs2, td = 0;

	for(s = all; s != NULL; s = s->hh.next) {

		cs1 = 0;
		cs2 = 0;

		while((tmp = (char **) utarray_next(t1, tmp))) {

			if(strcmp(*tmp, s->value) == 0)
				cs1++;

		}

		while((tmp = (char **) utarray_next(t2, tmp))) {

			if(strcmp(*tmp, s->value) == 0)
				cs2++;

		}

		if(cs1 > cs2)
			td += (cs1 - cs2);
		else
			td += (cs2 - cs1);

	}

	utarray_free(t1);
	utarray_free(t2);

	hash_token_free(h1);
	hash_token_free(h2);
	hash_token_free(all);

	return td;

}

int block_distance(const char * str1, const char *str2) {

	cost_t cost = {
			.max_cost = 0,
			.min_cost = 0,
			.gap_cost = 0,
			.tok_str = WHITESPACE_DELIMITERS
	};

	return block_distance_custom(str1, str2, &cost);

}

float block_distance_similarity_custom(const char *str1, const char *str2, cost_t *cost) {

	UT_array *strs1 = tokenize_to_utarray(str1, cost->tok_str);
	UT_array *strs2 = tokenize_to_utarray(str2, cost->tok_str);

	float ret;
	float t_pos = ((float) utarray_len(strs1)) + ((float) utarray_len (strs2));
	float t_dis = (float) block_distance_custom(str1, str2, cost);

	ret = (t_pos - t_dis) / t_pos;

	utarray_free(strs1);
	utarray_free(strs2);

	return ret;

}

float block_distance_similarity(const char *str1, const char *str2) {

	cost_t cost = {
			.max_cost = 0,
			.min_cost = 0,
			.gap_cost = 0,
			.tok_str = WHITESPACE_DELIMITERS
	};

	return block_distance_similarity_custom(str1, str2, &cost);

}

