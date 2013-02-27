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
 * cost.c
 *
 *  Created on: 20 Nov 2012
 *      Author: Johnathan Botha <jokillsya@gmail.com>
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "cost.h"

const char *APPROX[7] = { "dt", "gj", "lr", "mn", "bpv", "aeiou", ",." };

static float _affine_gap_1_over_3(const int idx_start, const int idx_end) {

	if (idx_start >= idx_end)
		return ((float) 0);
	else
		return (((float) 1) + (((idx_end - 1) - idx_start) * (((float) 1) / ((float) 3))));

}

static float _affine_gap_5_1(const int idx_start, const int idx_end) {

	if (idx_start >= idx_end)
		return ((float) 0);
	else
		return (((float) 5) + ((idx_end - 1) - idx_start));

}

static float _sub_cost_1(const char * str1, const int str1_idx, const char *str2, const int str2_idx) {

	if (str1[str1_idx] == str2[str2_idx])
		return ((float) 0);
	else
		return ((float) 1);

}

static float _sub_cost_1_min_2(const char * str1, const int str1_idx, const char *str2, const int str2_idx) {

	size_t l1 = strlen(str1);
	size_t l2 = strlen(str2);

	if (((int) l1 <= str1_idx) || (str1_idx < 0))
		return ((float) 0);

	if (((int) l2 <= str2_idx) || (str2_idx < 0))
		return ((float) 0);

	if (str1[str1_idx] == str2[str2_idx])
		return ((float) 1);
	else
		return ((float) -2);

}

static float _sub_cost_5_3_min_3(const char * str1, const int str1_idx, const char *str2, const int str2_idx) {

	size_t l1 = strlen(str1);
	size_t l2 = strlen(str2);

	if (((int) l1 <= str1_idx) || (str1_idx < 0))
		return (CHR_MIS_SCORE);

	if (((int) l2 <= str2_idx) || (str2_idx < 0))
		return (CHR_MIS_SCORE);

	if (str1[str1_idx] == str2[str2_idx]) {

		return (CHR_EXT_SCORE);

	} else {

		int i;

		char c1 = tolower(str1[str1_idx]);
		char c2 = tolower(str2[str2_idx]);

		for (i = 0; i < 7; i++) {
			if ((strchr(APPROX[i], c1) != NULL ) && (strchr(APPROX[i], c2) != NULL))
				return (CHR_APR_SCORE);
		}

		return (CHR_MIS_SCORE);

	}

}

affine_idx_cost_t* affine_gap_1_over_3() {

	cost_t *cost = malloc(sizeof(cost_t));
	affine_idx_cost_t *sub_cost = malloc(sizeof(affine_idx_cost_t));

	cost->max_cost = 1;
	cost->min_cost = 0;
	cost->gap_cost = 0;

	sub_cost->cost = cost;
	sub_cost->cost_func = &_affine_gap_1_over_3;

	return (sub_cost);

}

affine_idx_cost_t* affine_gap_5_1() {

	cost_t *cost = malloc(sizeof(cost_t));
	affine_idx_cost_t *sub_cost = malloc(sizeof(affine_idx_cost_t));

	cost->max_cost = 5;
	cost->min_cost = 0;
	cost->gap_cost = 0;

	sub_cost->cost = cost;
	sub_cost->cost_func = &_affine_gap_5_1;

	return (sub_cost);

}

sub_cost_t* sub_cost_1() {

	cost_t *cost = malloc(sizeof(cost_t));
	sub_cost_t *sub_cost = malloc(sizeof(sub_cost_t));

	cost->max_cost = 1;
	cost->min_cost = 0;
	cost->gap_cost = 0;

	sub_cost->cost = cost;
	sub_cost->cost_func = &_sub_cost_1;

	return (sub_cost);

}

sub_cost_t* sub_cost_1_min_2() {

	cost_t *cost = malloc(sizeof(cost_t));
	sub_cost_t *sub_cost = malloc(sizeof(sub_cost_t));

	cost->max_cost = 1;
	cost->min_cost = -2;
	cost->gap_cost = 0.5;

	sub_cost->cost = cost;
	sub_cost->cost_func = &_sub_cost_1_min_2;

	return (sub_cost);
}

sub_cost_t* sub_cost_5_3_min_3() {

	cost_t *cost = malloc(sizeof(cost_t));
	sub_cost_t *sub_cost = malloc(sizeof(sub_cost_t));

	cost->max_cost = 5;
	cost->min_cost = -3;
	cost->gap_cost = 0;

	sub_cost->cost = cost;
	sub_cost->cost_func = &_sub_cost_5_3_min_3;

	return (sub_cost);
}

const cost_t *extract_cost(const void *v_conf, cost_type_e cost_type) {

	const cost_t *cost_conf_ptr;

	switch (cost_type) {
	case COST:
		cost_conf_ptr = (cost_t *)v_conf;
		break;
	case SUB_COST:
		cost_conf_ptr = ((sub_cost_t *)v_conf)->cost;
		break;
	case AFFINE_COST:
		cost_conf_ptr = ((affine_cost_t *)v_conf)->cost;
		break;
	case AFFINE_IDX_COST:
		cost_conf_ptr = ((affine_idx_cost_t *)v_conf)->cost;
		break;
	case COMP_COST:
		cost_conf_ptr = ((comp_cost_t *)v_conf)->sub_cost->cost;
		break;
	case COMP_IDX_COST:
		cost_conf_ptr = ((comp_idx_cost_t *)v_conf)->sub_cost->cost;
		break;
	case WIN_COMP_IDX_COST:
		cost_conf_ptr = ((w_comp_idx_cost_t *)v_conf)->comp_conf->sub_cost->cost;
		break;
	default:
		return (NULL);
	}

	return (cost_conf_ptr);

}

void free_affine_sub_cost(affine_idx_cost_t *cost) {

	free(cost->cost);
	free(cost);

}

void free_sub_cost(sub_cost_t *cost) {

	free(cost->cost);
	free(cost);

}

