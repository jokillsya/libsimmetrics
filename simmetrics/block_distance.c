/*
 * block_distance.c
 *
 *  Created on: 05 Dec 2012
 *      Author: johnathan
 */
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cost.h"
#include "utlist.h"
#include "utarray.h"
#include "uthash.h"
#include "tokenizer.h"

int block_distance_custom(const char * str1, const char *str2, std_tokenizer_t *tokenizer) {

	UT_array *t1 = tokenizer->tok_utarr_func(str1, tokenizer->delimiters);
	UT_array *t2 = tokenizer->tok_utarr_func(str2, tokenizer->delimiters);

	hash_token_t *h1 = tokenizer->tok_uq_hash_func(str1, tokenizer->delimiters);
	hash_token_t *h2 = tokenizer->tok_uq_hash_func(str2, tokenizer->delimiters);

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

	std_tokenizer_t tokenizer = {
			.delimiters = WHITESPACE_DELIMITERS,
			.tok_utarr_func = &tokenize_to_utarray,
			.tok_uq_hash_func = &uq_tokenize_to_hash
	};

	return block_distance_custom(str1, str2, &tokenizer);

}

float block_distance_similarity_custom(const char *str1, const char *str2, std_tokenizer_t *tokenizer) {

	UT_array *strs1 = tokenizer->tok_utarr_func(str1, tokenizer->delimiters);
	UT_array *strs2 = tokenizer->tok_utarr_func(str2, tokenizer->delimiters);

	float ret;
	float t_pos = ((float) utarray_len(strs1)) + ((float) utarray_len (strs2));
	float t_dis = (float) block_distance_custom(str1, str2, tokenizer);

	ret = (t_pos - t_dis) / t_pos;

	utarray_free(strs1);
	utarray_free(strs2);

	return ret;

}

float block_distance_similarity(const char *str1, const char *str2) {

	std_tokenizer_t tokenizer = {
			.delimiters = WHITESPACE_DELIMITERS,
			.tok_utarr_func = &tokenize_to_utarray,
			.tok_uq_hash_func = &uq_tokenize_to_hash
	};

	return block_distance_similarity_custom(str1, str2, &tokenizer);

}

