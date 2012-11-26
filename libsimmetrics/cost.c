/*
 * cost.c
 *
 *  Created on: 20 Nov 2012
 *      Author: johnathan
 */

#include "cost.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

const char *APPROX[7] = {
		"dt",
		"gj",
		"lr",
		"mn",
		"bpv",
		"aeiou",
		",."
};

static float _affine_gap_1_over_3(const int idx_start, const int idx_end) {

	if(idx_start >= idx_end)
		return (float)0;
	else
		return ((float)1) + (((idx_end - 1) - idx_start) * (((float)1) / ((float)3)));

}

static float _affine_gap_5_1(const int idx_start, const int idx_end) {

	if(idx_start >= idx_end)
		return (float)0;
	else
		return ((float)5) + ((idx_end - 1) - idx_start);

}

static float _sub_cost_1(const char * str1, const int str1_idx, const char *str2, const int str2_idx) {

	if(str1[str1_idx] == str2[str2_idx])
		return (float)0;
	else
		return (float)1;

}

static float _sub_cost_1_min_2(const char * str1, const int str1_idx, const char *str2, const int str2_idx) {

	size_t l1 = strlen(str1);
	size_t l2 = strlen(str2);

    if (((int)l1 <= str1_idx) || (str1_idx < 0))
        return (float)0;

    if (((int)l2 <= str2_idx) || (str2_idx < 0))
        return (float)0;

	if(str1[str1_idx] == str2[str2_idx])
		return (float)1;
	else
		return (float)-2;

}

static float _sub_cost_5_3_min_3(const char * str1, const int str1_idx, const char *str2, const int str2_idx) {

	size_t l1 = strlen(str1);
	size_t l2 = strlen(str2);

    if (((int)l1 <= str1_idx) || (str1_idx < 0))
        return CHR_MIS_SCORE;

    if (((int)l2 <= str2_idx) || (str2_idx < 0))
        return CHR_MIS_SCORE;

    if(str1[str1_idx] == str2[str2_idx]) {

    	return CHR_EXT_SCORE;

    } else {

    	int i;

    	char c1 = tolower(str1[str1_idx]);
    	char c2 = tolower(str2[str2_idx]);

    	for(i = 0; i < 7; i++) {
    		if((strchr(APPROX[i], c1) != NULL) && (strchr(APPROX[i], c2) != NULL))
    			return CHR_APR_SCORE;
    	}

    	return CHR_MIS_SCORE;

    }

}

affine_idx_cost_t affine_gap_1_over_3() {

	cost_t cost = {
			.max_cost = 1,
			.min_cost = 0,
			.gap_cost = 0
	};

	affine_idx_cost_t sub_cost = {

			.cost = cost,
			.cost_func = &_affine_gap_1_over_3

	};

	return sub_cost;

}

affine_idx_cost_t affine_gap_5_1() {

	cost_t cost = {
			.max_cost = 5,
			.min_cost = 0,
			.gap_cost = 0
	};

	affine_idx_cost_t sub_cost = {
			.cost = cost,
			.cost_func = &_affine_gap_5_1
	};

	return sub_cost;

}

sub_cost_t sub_cost_1() {

	cost_t cost = {
			.max_cost = 1,
			.min_cost = 0,
			.gap_cost = 0
	};

	sub_cost_t sub_cost = {
			.cost = cost,
			.cost_func = &_sub_cost_1
	};

	return sub_cost;

}

sub_cost_t sub_cost_1_min_2() {

	cost_t cost = {
			.max_cost = 1,
			.min_cost = -2,
			.gap_cost = 0.5
	};

	sub_cost_t sub_cost = {
			.cost = cost,
			.cost_func = &_sub_cost_1_min_2
	};

	return sub_cost;
}

sub_cost_t sub_cost_5_3_min_3() {

	cost_t cost = {
			.max_cost = 5,
			.min_cost = -3,
			.gap_cost = 0
	};

	sub_cost_t sub_cost = {
			.cost = cost,
			.cost_func = &_sub_cost_5_3_min_3
	};

	return sub_cost;
}

