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
 * needleman_wunch.c
 *
 *  Created on: 23 Nov 2012
 *      Author: Johnathan Botha <jokillsya@gmail.com>
 */
#include <stdlib.h>
#include <string.h>
#include "cost.h"
#include "util.h"
#include "needleman_wunch.h"

float needleman_wunch_custom(const char *str1, const char *str2,
		const void *v_conf) {

	const sub_cost_t *conf = v_conf;

	int n = strlen(str1);
	int m = strlen(str2);

	int i, j;
	float cost;

	if ((n == 0) || (m == 0)) {
		return (0);
	}

	float d[n + 1][m + 1];

	for (i = 0; i <= n; i++)
		d[i][0] = i;

	for (j = 0; j <= m; j++)
		d[0][j] = j;

	for (i = 1; i <= n; i++) {

		for (j = 1; j <= m; j++) {

			cost = conf->cost_func(str1, i - 1, str2, j - 1);
			d[i][j] = MIN3(	d[i - 1][j] + conf->cost->gap_cost,
							d[i][j - 1] + conf->cost->gap_cost,
							d[i - 1][j - 1] + cost);

		}

	}

	return (d[n][m]);

}

float needleman_wunch(const char *str1, const char *str2) {

	sub_cost_t *sub_cost = sub_cost_1();
	sub_cost->cost->gap_cost = 2;

	float ret = needleman_wunch_custom(str1, str2, sub_cost);

	free(sub_cost->cost);
	free(sub_cost);

	return (ret);

}

float needleman_wunch_similarity_custom(const char *str1, const char *str2,
		const void *v_conf) {

	const sub_cost_t *conf = v_conf;

	float nw = needleman_wunch_custom(str1, str2, conf);

	float l1 = ((float) strlen(str1));
	float l2 = ((float) strlen(str2));
	float max_val = MAX(l1, l2);
	float min_val = max_val;

	if (conf->cost->max_cost > conf->cost->gap_cost)
		max_val *= conf->cost->max_cost;
	else
		max_val *= conf->cost->gap_cost;

	if (conf->cost->min_cost < conf->cost->gap_cost)
		min_val *= conf->cost->min_cost;
	else
		min_val *= conf->cost->gap_cost;

	if (min_val < 0) {

		max_val -= min_val;
		nw -= min_val;

	}

	if (max_val == 0)
		return (0);
	else
		return (1 - (nw / max_val));

}

float needleman_wunch_similarity(const char *str1, const char *str2) {

	sub_cost_t *sub_cost = sub_cost_1();
	sub_cost->cost->gap_cost = 2;

	float ret = needleman_wunch_similarity_custom(str1, str2, sub_cost);

	free(sub_cost->cost);
	free(sub_cost);

	return (ret);

}

