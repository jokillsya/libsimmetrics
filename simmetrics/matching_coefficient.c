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
 * matching_coeficcient.c
 *
 *  Created on: 11 Dec 2012
 *      Author: Johnathan Botha <jokillsya@gmail.com>
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cost.h"
#include "utlist.h"
#include "utarray.h"
#include "uthash.h"
#include "util.h"
#include "tokenizer.h"
#include "matching_coefficient.h"

float matching_coefficient_custom(const char *str1, const char *str2, const void *v_tokenizer) {

	const std_tokenizer_t *tokenizer = v_tokenizer;


	UT_array *t1 = tokenizer->tok_utarr_func(str1, tokenizer->delimiters);
	UT_array *t2 = tokenizer->tok_utarr_func(str2, tokenizer->delimiters);

	char **tmp1 = NULL, **tmp2 = NULL;
	int tf = 0;

	while((tmp1 = (char **) utarray_next(t1, tmp1))) {

		while((tmp2 = (char **) utarray_next(t2, tmp2))) {

			if(strcmp(*tmp1, *tmp2) == 0) {

				tf++;
				break;

			}

		}

	}

	utarray_free(t1);
	utarray_free(t2);

	return ((float) tf);

}

float matching_coefficient(const char *str1, const char *str2) {

	std_tokenizer_t tokenizer = {
			.delimiters = WHITESPACE_DELIMITERS,
			.tok_utarr_func = &tokenize_to_utarray,
			.tok_uq_hash_func = &uq_tokenize_to_hash
	};

	return (matching_coefficient_custom(str1, str2, &tokenizer));

}

float matching_coefficient_similarity_custom(const char *str1, const char *str2, const void *v_tokenizer) {

	const std_tokenizer_t *tokenizer = v_tokenizer;


	UT_array *tm1 = tokenizer->tok_utarr_func(str1, tokenizer->delimiters);
	UT_array *tm2 = tokenizer->tok_utarr_func(str2, tokenizer->delimiters);

	const int tot_p = MAX(utarray_len(tm1), utarray_len(tm2));

	float ret = matching_coefficient_custom(str1, str2, tokenizer) / (float) tot_p;

	utarray_free(tm1);
	utarray_free(tm2);

	return (ret);

}

float matching_coefficient_similarity(const char *str1, const char *str2) {

	std_tokenizer_t tokenizer = {
			.delimiters = WHITESPACE_DELIMITERS,
			.tok_utarr_func = &tokenize_to_utarray,
			.tok_uq_hash_func = &uq_tokenize_to_hash
	};

	return (matching_coefficient_similarity_custom(str1, str2, &tokenizer));

}

