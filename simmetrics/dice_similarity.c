/*
 * dice_similarity.c
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

const float dice_similarity_custom(const char *str1, const char *str2, cost_t *cost) {

	hash_token_t *h1 = uq_tokenize_to_hash(str1, cost->tok_str);
	hash_token_t *h2 = uq_tokenize_to_hash(str2, cost->tok_str);

	hash_token_t *all = merge_tokens(h1, h2);

	unsigned int ch1 = HASH_COUNT(h1), ch2 = HASH_COUNT(h2), ch3 = HASH_COUNT(all);
	unsigned int ct = (ch1 + ch2) - ch3;

	const float ret = ((float) 2.0 * (float) ct) / (ch1 + ch2);

	hash_token_free(h1);
	hash_token_free(h2);
	hash_token_free(all);

	return ret;

}

const float dice_similarity(const char *str1, const char *str2) {

	cost_t cost = {
			.max_cost = 0,
			.min_cost = 0,
			.gap_cost = 0,
			.tok_str = WHITESPACE_DELIMITERS
	};

	return dice_similarity_custom(str1, str2, &cost);

}

