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
 * monge_elkan.c
 *
 *  Created on: 26 Nov 2012
 *      Author: Johnathan Botha <jokillsya@gmail.com>
 */

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "util.h"
#include "uthash.h"
#include "utarray.h"
#include "cost.h"
#include "monge_elkan.h"
#include "smith_waterman_gotoh.h"
#include "tokenizer.h"

float monge_elkan_similarity_custom(const char *str1, const char *str2,
		const void *v_conf) {

//	cost_type_e cost_type = WIN_COMP_IDX_COST;
	char *tok_str = WHITESPACE_DELIMITERS;
	float sum_matches = 0;
	float max_found;
	float found = 0;

	int tok1_cnt = 0;

	char str1_arr[strlen(str1) + 1];
	char str2_arr[strlen(str2) + 1];
	strcpy(str1_arr, str1);

	char *l, *r, *brkt, *brkb;

	for (l = strtok_r(str1_arr, tok_str, &brkt); l;
			l = strtok_r(NULL, tok_str, &brkt)) {

		strcpy(str2_arr, str2);
		tok1_cnt++;
		max_found = 0;

		for (r = strtok_r(str2_arr, tok_str, &brkb); r;
				r = strtok_r(NULL, tok_str, &brkb)) {

			found = smith_waterman_gotoh_similarity_custom(l, r, v_conf);

			if (found > max_found)
				max_found = found;

		}

		sum_matches += max_found;

	}

	return (sum_matches / (float) tok1_cnt);

}

float monge_elkan_similarity(const char *str1, const char *str2) {

	float ret;

	affine_idx_cost_t *aff_idx_c = affine_gap_5_1();
	sub_cost_t *sub_cost = sub_cost_5_3_min_3();

	comp_idx_cost_t comp_cost = { .gap_cost = aff_idx_c, .sub_cost = sub_cost };

	w_comp_idx_cost_t conf = { .win_size = 100, .comp_conf = &comp_cost };

	ret = monge_elkan_similarity_custom(str1, str2, &conf);

	free_affine_sub_cost(aff_idx_c);
	free_sub_cost(sub_cost);

	return (ret);

}

