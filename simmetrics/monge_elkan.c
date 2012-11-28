/*
 * monge_elkan.c
 *
 *  Created on: 26 Nov 2012
 *      Author: johnathan
 */

#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include "cost.h"
#include "simmetrics.h"
#include "monge_elkan.h"

float custom_monge_elkan(const char *str1, const char *str2, metric_function_t *metric, const void *v_conf, const cost_type_e cost_type) {

	const cost_t *cost_conf_ptr = extract_cost(v_conf, cost_type);

	float sum_matches = 0;
	float max_found;
	float found = 0;

	int tok1_cnt = 0;

	char str1_arr[strlen(str1) + 1];
	char str2_arr[strlen(str2) + 1];
	strcpy(str1_arr, str1);

	char *l, *r, *brkt, *brkb;

	for (l = strtok_r(str1_arr, cost_conf_ptr->tok_str, &brkt); l; l = strtok_r(NULL, cost_conf_ptr->tok_str, &brkt)) {

		strcpy(str2_arr, str2);

		tok1_cnt++;

		max_found = 0;

		for (r = strtok_r(str2_arr, cost_conf_ptr->tok_str, &brkb); r; r = strtok_r(NULL, cost_conf_ptr->tok_str, &brkb)) {
			found = metric->custom_metric_func(str1, str2, v_conf);
			if (found > max_found)
				max_found = found;
		}

		sum_matches += max_found;

	}

	return (sum_matches / (float) tok1_cnt);

}

float monge_elkan(const char *str1, const char *str2) {

	comp_idx_cost_t comp_cost = {
			.gap_cost = affine_gap_5_1(),
			.sub_cost = sub_cost_5_3_min_3()
	};

	comp_cost.sub_cost->cost->tok_str = WHITESPACE_DELIMITERS;

	w_comp_idx_cost_t conf = {
			.win_size = 100,
			.comp_conf = &comp_cost
	};

	metric_function_t metric_func;
	metric_func.custom_metric_func = &custom_smith_waterman_gotoh_similarity;

	return custom_monge_elkan(str1, str2, &metric_func, &conf, WIN_COMP_IDX_COST);

}

