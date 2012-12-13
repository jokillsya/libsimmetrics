/*
 * dice_similarity.c
 *
 *  Created on: 10 Dec 2012
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

const float dice_similarity_custom(const char *str1, const char *str2, std_tokenizer_t *tokenizer) {

	hash_token_t *h1 = tokenizer->tok_uq_hash_func(str1, tokenizer->delimiters);
	hash_token_t *h2 = tokenizer->tok_uq_hash_func(str2, tokenizer->delimiters);

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

	std_tokenizer_t tokenizer = {
			.delimiters = WHITESPACE_DELIMITERS,
			.tok_utarr_func = &tokenize_to_utarray,
			.tok_uq_hash_func = &uq_tokenize_to_hash
	};

	return dice_similarity_custom(str1, str2, &tokenizer);

}

