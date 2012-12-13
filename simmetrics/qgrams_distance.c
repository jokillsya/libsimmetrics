/*
 * qgrams_distance.c
 *
 *  Created on: 11 Dec 2012
 *      Author: johnathan
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "cost.h"
#include "uthash.h"
#include "utarray.h"
#include "tokenizer.h"
#include "qgrams_distance.h"

const float qgrams_distance_custom(const char *str1, const char *str2, qgram_tokenizer_t *tokenizer) {

	UT_array *t1 = tokenizer->tok_utarr_func(str1, tokenizer->qgram);
	UT_array *t2 = tokenizer->tok_utarr_func(str2, tokenizer->qgram);

	hash_token_t *h1 = tokenizer->tok_uq_hash_func(str1, tokenizer->qgram);
	hash_token_t *h2 = tokenizer->tok_uq_hash_func(str2, tokenizer->qgram);

	hash_token_t *all = merge_tokens(h1, h2);
	hash_token_t *s;

	int cs1, cs2;
	float td = 0;

	char **tmp;

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

	return (float)td;

}

const float qgrams_distance(const char *str1, const char *str2) {

	qgram_t type = { .qgram_len = QGRAM_3, .extended = true };

	qgram_tokenizer_t tokenizer = {
			.qgram = &type,
			.tok_utarr_func = &qgram_tokenize_to_utarray,
			.tok_uq_hash_func = &qgram_uq_tokenize_to_hash
	};

	return qgrams_distance_custom(str1, str2, &tokenizer);

}

const float qgrams_distance_similarity_custom(const char *str1, const char *str2, qgram_tokenizer_t *tokenizer) {

	UT_array *tm1 = tokenizer->tok_utarr_func(str1, tokenizer->qgram);
	UT_array *tm2 = tokenizer->tok_utarr_func(str2, tokenizer->qgram);

	const int l1 = utarray_len(tm1);
	const int l2 = utarray_len(tm2);

	const int m = l1 + l2;

	float ret;

	if(m == 0)
		ret = 0;
	else
		ret = (m - qgrams_distance_custom(str1, str2, tokenizer)) / m;

	utarray_free(tm1);
	utarray_free(tm2);

	return (const float) ret;

}

const float qgrams_distance_similarity(const char *str1, const char *str2) {

	qgram_t type = { .qgram_len = QGRAM_3, .extended = true };

	qgram_tokenizer_t tokenizer = {
			.qgram = &type,
			.tok_utarr_func = &qgram_tokenize_to_utarray,
			.tok_uq_hash_func = &qgram_uq_tokenize_to_hash
	};

	return qgrams_distance_similarity_custom(str1, str2, &tokenizer);

}

