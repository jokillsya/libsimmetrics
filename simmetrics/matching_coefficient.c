/*
 * matching_coeficcient.c
 *
 *  Created on: 11 Dec 2012
 *      Author: johnathan
 */

#include <stdlib.h>
#include <string.h>
#include "cost.h"
#include "utlist.h"
#include "utarray.h"
#include "uthash.h"
#include "util.h"
#include "tokenizer.h"
#include "matching_coefficient.h"

const float matching_coefficient_custom(const char *str1, const char *str2, cost_t *cost) {

	UT_array *t1 = tokenize_to_utarray(str1, cost->tok_str);
	UT_array *t2 = tokenize_to_utarray(str2, cost->tok_str);

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

	return (const float) tf;

}

const float matching_coefficient(const char *str1, const char *str2) {

	cost_t cost = {
			.max_cost = 0,
			.min_cost = 0,
			.gap_cost = 0,
			.tok_str = WHITESPACE_DELIMITERS
	};

	return matching_coefficient_custom(str1, str2, &cost);

}

const float matching_coefficient_similarity_custom(const char *str1, const char *str2, cost_t *cost) {

	UT_array *tm1 = tokenize_to_utarray(str1, cost->tok_str);
	UT_array *tm2 = tokenize_to_utarray(str2, cost->tok_str);

	const int tot_p = MAX(utarray_len(tm1), utarray_len(tm2));

	const float ret = matching_coefficient_custom(str1, str2, cost) / (const float) tot_p;

	utarray_free(tm1);
	utarray_free(tm2);

	return ret;

}

const float matching_coefficient_similarity(const char *str1, const char *str2) {

	cost_t cost = {
			.max_cost = 0,
			.min_cost = 0,
			.gap_cost = 0,
			.tok_str = WHITESPACE_DELIMITERS
	};

	return matching_coefficient_similarity_custom(str1, str2, &cost);

}

