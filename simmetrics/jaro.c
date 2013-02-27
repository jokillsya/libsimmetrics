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
 * jaro.c
 *
 *  Created on: 20 Nov 2012
 *      Author: Johnathan Botha <jokillsya@gmail.com>
 */

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include "jaro.h"
#include "util.h"

static char *get_common_chars(const char *str1, const char *str2,
		const int d_step) {

	char *ret_str;
	char ret[strlen(str1) + 1];
	char copy[strlen(str2) + 1];
	int i, j, k = 0;

	strcpy(copy, str2);

	for (i = 0; i < (int) strlen(str1); i++) {

		char tmp = str1[i];

		int max = MAX(0, (i - d_step));
		int min = MIN(i + d_step, ((int)strlen(str2) - 1));

		for (j = max; j < min; j++) {

			if (copy[j] == tmp) {

				ret[k] = tmp;
				copy[j] = (char) 0;
				k++;

				break;

			}

		}

	}

	ret[k++] = '\0';
	ret_str = malloc(sizeof(ret) * strlen(ret));
	strcpy(ret_str, ret);

	return (ret_str);

}

float jaro_similarity(const char *str1, const char *str2) {

	int halflen = ((MIN(strlen(str1), strlen(str2))) / 2)
			+ ((MIN(strlen(str1), strlen(str2))) % 2);

	char *com1 = get_common_chars(str1, str2, halflen);
	char *com2 = get_common_chars(str2, str1, halflen);

	int c1_len = strlen(com1);
	int c2_len = strlen(com2);
	int s1_len = strlen(str1);
	int s2_len = strlen(str2);

	if ((c1_len == 0) || (c2_len == 0)) {

		return (0.0);

	}

	if (c1_len != c2_len) {

		return (0.0);

	}

	int i;
	int trans = 0;

	for (i = 0; i < c1_len; i++) {

		if (com1[i] != com2[i]) {

			trans++;

		}

	}

	free(com1);
	free(com2);

	trans /= (float) 2;

	return (((float) c1_len / ((float) s1_len)
			+ (float) c2_len / ((float) s2_len)
			+ ((float) c1_len - (float) trans) / ((float) c1_len)) / ((float) 3));

}

