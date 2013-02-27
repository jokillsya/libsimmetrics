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
 * NOTE: I'm not sure how the licensing works across languages... If I screwed up
 * 			please let me know...
 *
 * soundex.c
 *
 * Ported from the Apache codec Java code.
 *
 *  Created on: 20 Nov 2012
 *      Author: The Apache Software Foundation <http://commons.apache.org/codec/>
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "soundex.h"
#include "smith_waterman_gotoh.h"

const char US_EN_MAP[] = "01230120022455012623010202";

static char map(const char _ch) {

	int index = _ch - 'A';

	if ((index < 0) || (index >= ((int) strlen(US_EN_MAP)))) {

		return ('\0');

	}

	return (US_EN_MAP[index]);

}

static char get_mapping_code(const char *str, const int index) {

	char m_chr = map(str[index]);

	if (m_chr == '\0') {

		return ('\0');

	}

	if (index > 1 && m_chr != '0') {

		char hw_chr = str[index - 1];

		if ('H' == hw_chr || 'W' == hw_chr) {

			char pre_hw_char = str[index - 2];
			char f_code = map(pre_hw_char);

			if ((f_code == m_chr) || ('H' == pre_hw_char) || ('W' == pre_hw_char)) {

				m_chr = 0;

			}

		}

	}

	return (m_chr);

}

/**
 * Clean up the string - returned string must be freed be caller.
 */
static char* clean(const char *str) {

	int len = strlen(str);
	char *res;

	if (len == 0) {

		res = malloc(sizeof(str));
		res[0] = '\0';
		return (res);

	} else {

		res = malloc(sizeof(str) * len);
		char chars[len];
		int cnt = 0, i;

		for (i = 0; i < len; i++) {

			if (isalpha(str[i])) {

				chars[cnt++] = str[i];

			}

		}

		if (cnt == len) {

			for (i = 0; i < len; i++) {

				res[i] = toupper(str[i]);

			}

		} else {

			//Get rid of anything that isn't alpha...
			for (i = 0; i < cnt; i++) {

				res[i] = toupper(chars[i]);

			}

		}

	}

	return (res);

}

char *soundex(const char *_str) {

	if (_str == NULL ) {
		return NULL ;
	}

	const char *str = clean(_str);

	if (strlen(str) == 0) {
		free((char*) str);
		return NULL ;
	}

	char out[] = { '0', '0', '0', '0', '\0' };
	char last, mapped;
	int incount = 1, count = 1;

	out[0] = str[0];

	last = get_mapping_code(str, 0);

	while (incount < ((int) strlen(str)) && count < ((int) strlen(out))) {

		mapped = get_mapping_code(str, incount++);

		if (mapped != 0) {

			if (mapped != '0' && mapped != last) {

				out[count++] = mapped;

			}

			last = mapped;

		}

	}

	char *ret = malloc(sizeof(out) * (strlen(out) + 1));
	ret[strlen(out) + 1] = '\0';
	strcpy(ret, out);
	free((char*) str);

	return (ret);
}

float soundex_similarity(const char *str1, const char *str2) {

	char *s1 = soundex(str1);
	char *s2 = soundex(str2);

	float res = smith_waterman_gotoh_similarity(s1, s2);

	free(s1);
	free(s2);

	return (res);

}

