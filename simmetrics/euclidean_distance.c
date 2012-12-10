/*
 * euclidean_distance.c
 *
 *  Created on: 10 Dec 2012
 *      Author: johnathan
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cost.h"
#include "uthash.h"
#include "utarray.h"
#include "tokenizer.h"
#include "euclidean_distance.h"

const float euclidean_distance_custom(const char *str1, const char *str2, cost_t *cost) {

	UT_array *t1 = tokenize_to_utarray(str1, cost->tok_str);
	UT_array *t2 = tokenize_to_utarray(str2, cost->tok_str);

	hash_token_t *h1 = uq_tokenize_to_hash(str1, cost->tok_str);
	hash_token_t *h2 = uq_tokenize_to_hash(str2, cost->tok_str);

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

		td += (float)(((float)cs1 - (float)cs2) * ((float)cs1 - (float)cs2));

	}

	utarray_free(t1);
	utarray_free(t2);

	hash_token_free(h1);
	hash_token_free(h2);
	hash_token_free(all);

	return sqrtf(td);

}

const float euclidean_distance(const char *str1, const char *str2) {

	cost_t cost = {
			.max_cost = 0,
			.min_cost = 0,
			.gap_cost = 0,
			.tok_str = WHITESPACE_DELIMITERS
	};

	return euclidean_distance_custom(str1, str2, &cost);

}

const float euclidean_distance_similarity_custom(const char *str1, const char *str2, cost_t * cost) {

	UT_array *tokarr1 = tokenize_to_utarray(str1, cost->tok_str);
	UT_array *tokarr2 = tokenize_to_utarray(str2, cost->tok_str);

	const float tl1 = utarray_len(tokarr1), tl2 = utarray_len(tokarr2);
	const float tp = sqrtf((tl1 * tl1) + (tl2 * tl2));
	const float td = euclidean_distance_custom(str1, str2, cost);

	utarray_free(tokarr1);
	utarray_free(tokarr2);

	return (tp - td) / tp;

}

const float euclidean_distance_similarity(const char *str1, const char *str2) {

	cost_t cost = {
			.max_cost = 0,
			.min_cost = 0,
			.gap_cost = 0,
			.tok_str = WHITESPACE_DELIMITERS
	};

	return euclidean_distance_similarity_custom(str1, str2, &cost);

}
