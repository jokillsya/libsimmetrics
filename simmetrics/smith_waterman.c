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
 * smith_waterman.c
 *
 *  Created on: 21 Nov 2012
 *      Author: Johnathan Botha <jokillsya@gmail.com>
 */

#include <stdlib.h>
#include <string.h>
#include "cost.h"
#include "util.h"
#include "smith_waterman.h"

float smith_waterman_custom(const char *str1, const char *str2, const void *v_conf) {

	const sub_cost_t *sub_cost = v_conf;

	float cost;
	float max_so_far = (float) 0;

	int n = strlen(str1);
	int m = strlen(str2);
	int i, j;

	if ((n == 0) || (m == 0))
		return ((float) 0);

	float d[n][m];

	for (i = 0; i < n; i++) {

		cost = sub_cost->cost_func(str1, i, str2, 0);

		if (i == 0)
			d[0][0] = MAX3((float)0, -sub_cost->cost->gap_cost, cost);
		else
			d[i][0] = MAX3(0, d[i - 1][0] - sub_cost->cost->gap_cost, cost);

		if (d[i][0] > max_so_far)
			max_so_far = d[i][0];

	}

	for (j = 0; j < m; j++) {

		cost = sub_cost->cost_func(str1, 0, str2, j);

		if (j == 0)
			d[0][0] = MAX3(0, -sub_cost->cost->gap_cost, cost);
		else
			d[0][j] = MAX3(0, d[0][j-1] - sub_cost->cost->gap_cost, cost);

		if (d[0][j] > max_so_far)
			max_so_far = d[0][j];

	}

	for (i = 1; i < n; i++) {

		for (j = 1; j < m; j++) {

			cost = sub_cost->cost_func(str1, i, str2, j);

			d[i][j] = MAX4((float)0, (d[i - 1][j] - sub_cost->cost->gap_cost), (d[i][j - 1] - sub_cost->cost->gap_cost), (d[i - 1][j - 1] + cost));

			if (d[i][j] > max_so_far)
				max_so_far = d[i][j];

		}

	}

	return (max_so_far);

}

float smith_waterman(const char *str1, const char *str2) {

	return (smith_waterman_custom(str1, str2, sub_cost_1_min_2()));

}

float smith_waterman_similarity_custom(const char *str1, const char *str2, const void *v_conf) {

	const sub_cost_t *sub_cost = v_conf;

	float sw = smith_waterman_custom(str1, str2, sub_cost);
	float max_val = MIN(strlen(str1), strlen(str2));
	float ret;

	if(sub_cost->cost->max_cost > -sub_cost->cost->gap_cost)
		max_val *= sub_cost->cost->max_cost;
	else
		max_val *= -sub_cost->cost->gap_cost;

	if(max_val == 0)
		ret = (float)1;
	else
		ret = (sw / max_val);

	return (ret);

}

float smith_waterman_similarity(const char *str1, const char *str2) {

	return (smith_waterman_similarity_custom(str1, str2, sub_cost_1_min_2()));

}
