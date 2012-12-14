/*
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
 * jaro_winkler.c
 *
 *  Created on: 20 Nov 2012
 *      Author: Johnathan Botha <jokillsya@gmail.com>
 */

#include <string.h>
#include "jaro.h"
#include "util.h"
#include "jaro_winkler.h"

static int get_pref_length(const char *str1, const char *str2) {

	int ret = MIN3(MIN_PREF_LEN, strlen(str1), strlen(str2));
	int i;

	for(i = 0; i < ret; i++) {

		if(str1[i] != str2[i]) {
			ret = i;
			break;
		}

	}

	return ret;

}

float jaro_winkler_similarity(const char *str1, const char *str2) {

	float d = jaro_similarity(str1, str2);
	int pref_len = get_pref_length(str1, str2);
	return d + (((float) pref_len) * PREF_ADJ_SCALE * (((float)1.0) - d));

}

