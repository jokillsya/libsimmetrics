/*
 * jaro_winkler.c
 *
 *  Created on: 20 Nov 2012
 *      Author: johnathan
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

