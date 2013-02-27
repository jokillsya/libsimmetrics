/*
 * * Copyright (C) 2012 Johnathan Botha et al. All rights reserved.
 *
 * This file is part of libsimmetrics
 *
 * libsimmetrics is the C port of the Java project called Simmetrics,
 *
 * The Java code can be found here: https://github.com/Simmetrics/simmetrics
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * cosine_similarity.c
 *
 *  Created on: 10 Dec 2012
 *      Author: Johnathan Botha <jokillsya@gmail.com>
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "cost.h"
#include "uthash.h"
#include "utarray.h"
#include "tokenizer.h"

float cosine_similarity_custom(const char *str1, const char *str2, const void *v_tokenizer) {

	const std_tokenizer_t *tokenizer = v_tokenizer;

	hash_token_t *h1 = tokenizer->tok_uq_hash_func(str1, tokenizer->delimiters);
	hash_token_t *h2 = tokenizer->tok_uq_hash_func(str2, tokenizer->delimiters);

	hash_token_t *all = merge_tokens(h1, h2);

	unsigned int ch1 = HASH_COUNT(h1), ch2 = HASH_COUNT(h2), ch3 = HASH_COUNT(all);
	unsigned int ct = (ch1 + ch2) - ch3;

	const float ret = ((float)ct / (powf((float)ch1, (float)0.5) * powf((float)ch2, (float)0.5)));

	hash_token_free(h1);
	hash_token_free(h2);
	hash_token_free(all);

	return (ret);

}

float cosine_similarity(const char *str1, const char *str2) {

	std_tokenizer_t tokenizer = {
			.delimiters = WHITESPACE_DELIMITERS,
			.tok_utarr_func = &tokenize_to_utarray,
			.tok_uq_hash_func = &uq_tokenize_to_hash
	};

	return (cosine_similarity_custom(str1, str2, &tokenizer));

}

