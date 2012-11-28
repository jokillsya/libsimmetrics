/*
 * smith_waterman_gotoh.c
 *
 *  Created on: 22 Nov 2012
 *      Author: johnathan
 */

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "util.h"
#include "cost.h"
#include "smith_waterman_gotoh.h"

float custom_smith_waterman_gotoh(const char *str1, const char *str2, const w_comp_idx_cost_t *conf) {

	float cost;
	float max_so_far = 0;
	float max_gap_cost = 0;
	float max_gap_cost1 = 0;
	float max_gap_cost2 = 0;

	int n = strlen(str1);
	int m = strlen(str2);
	int i, j, k, w_st;

	if ((n == 0) || (m == 0))
		return (float) 0;

	float d[n][m];

	for (i = 0; i < n; i++) {

		cost = conf->comp_conf->sub_cost->cost_func(str1, i, str2, 0);

		if (i == 0)
			d[0][0] = MAX(0, cost);
		else {

			w_st = i - conf->win_size;

			if (w_st < 1)
				w_st = 1;

			for (k = w_st; k < i; k++)
				max_gap_cost = MAX(max_gap_cost, d[i - k][0] - conf->comp_conf->gap_cost->cost_func(i - k, i));

			d[i][0] = MAX3(0, max_gap_cost, cost);

		}

		if (d[i][0] > max_so_far)
			max_so_far = d[i][0];

	}

	for (j = 0; j < m; j++) {

		cost = conf->comp_conf->sub_cost->cost_func(str1, 0, str2, j);

		if (j == 0)
			d[0][0] = MAX(0, cost);
		else {

			max_gap_cost = 0;
			w_st = j - conf->win_size;

			if (w_st < 1)
				w_st = 1;

			for (k = w_st; k < j; k++)
				max_gap_cost = MAX(max_gap_cost, d[0][j - k] - conf->comp_conf->gap_cost->cost_func(j - k, j));

			d[0][j] = MAX3(0, max_gap_cost, cost);

		}

		if (d[0][j] > max_so_far)
			max_so_far = d[0][j];

	}

	for (i = 1; i < n; i++) {

		for (j = 1; j < m; j++) {

			cost = conf->comp_conf->sub_cost->cost_func(str1, i, str2, j);
			w_st = i - conf->win_size;

			if (w_st < 1)
				w_st = 1;

			for (k = w_st; k < i; k++)
				max_gap_cost1 = MAX(max_gap_cost1, d[i - k][j] - conf->comp_conf->gap_cost->cost_func(i - k, i));

			w_st = j - conf->win_size;

			if (w_st < 1)
				w_st = 1;

			for (k = w_st; k < j; k++)
				max_gap_cost2 = MAX(max_gap_cost2, d[i][j-k] - conf->comp_conf->gap_cost->cost_func(j - k, j));

			d[i][j] = MAX4(0, max_gap_cost1, max_gap_cost2, d[i - 1][j - 1] + cost);

			if (d[i][j] > max_so_far)
				max_so_far = d[i][j];

		}

	}

	return max_so_far;

}

float smith_waterman_gotoh(const char *str1, const char *str2) {

	comp_idx_cost_t comp_cost = {
			.gap_cost = affine_gap_5_1(),
			.sub_cost = sub_cost_5_3_min_3()
	};

	w_comp_idx_cost_t conf = {
			.win_size = 100,
			.comp_conf = &comp_cost
	};

	return custom_smith_waterman_gotoh(str1, str2, &conf);

}

float custom_smith_waterman_gotoh_similarity(const char *str1, const char *str2, const void *v_conf) {

	const w_comp_idx_cost_t *conf = v_conf;

	float sw_gotoh = custom_smith_waterman_gotoh(str1, str2, conf);
	float max_value = MIN((float)strlen(str1), (float)strlen(str2));
	float ret;

	if(conf->comp_conf->sub_cost->cost->max_cost > -conf->comp_conf->gap_cost->cost->max_cost)
		max_value *= conf->comp_conf->sub_cost->cost->max_cost;
	else
		max_value *= -conf->comp_conf->gap_cost->cost->max_cost;

	if(max_value == 0)
		ret = 0;
	else
		ret = (sw_gotoh / max_value);

	return ret;

}

float smith_waterman_gotoh_similarity(const char *str1, const char *str2) {

	comp_idx_cost_t comp_cost = {
			.gap_cost = affine_gap_5_1(),
			.sub_cost = sub_cost_5_3_min_3()
	};

	w_comp_idx_cost_t conf = {
			.win_size = 100,
			.comp_conf = &comp_cost
	};

	return custom_smith_waterman_gotoh_similarity(str1, str2, &conf);

}

