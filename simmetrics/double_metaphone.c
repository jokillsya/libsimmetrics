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
 * double_metaphone.c
 *
 *	This algorithm was ported from the Apache Codec project almost verbatim...
 *
 *  Created on: 22 Jan 2013
 *      Author: Johnathan Botha <jokillsya@gmail.com>
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include "double_metaphone.h"
#include "smith_waterman_gotoh.h"

#define MAX_MLEN 4

#define META_MALLOC(v,n,t) \
          (v = (t*)malloc(((n)*sizeof(t))))
#define META_REALLOC(v,n,t) \
	                  (v = (t*)realloc((v),((n)*sizeof(t))))
#define META_FREE(x) free((x))

metastring *
new_meta_string(const char *init_str) {
	metastring *s;
	char empty_string[] = "";

	META_MALLOC(s, 1, metastring);
	assert( s != NULL);

	if (init_str == NULL )
		init_str = empty_string;
	s->length = strlen(init_str);
	/* preallocate a bit more for potential growth */
	s->bufsize = s->length + 7;

	META_MALLOC(s->str, s->bufsize, char);
	assert( s->str != NULL);

	strncpy(s->str, init_str, s->length + 1);
	s->free_string_on_destroy = 1;

	return (s);
}

void free_meta_string(metastring * s) {
	if (s == NULL )
		return;

	if (s->free_string_on_destroy && (s->str != NULL ))
		META_FREE(s->str);

	META_FREE(s);
}

void inc_buffer(metastring * s, int chars_needed) {
	META_REALLOC(s->str, (s->bufsize + chars_needed + 10), char);
	assert( s->str != NULL);
	s->bufsize = s->bufsize + chars_needed + 10;
}

void make_upper(metastring * s) {
	char *i;

	for (i = s->str; *i; i++) {
		*i = toupper(*i);
	}
}

int is_vowel(metastring * s, int pos) {
	char c;

	if ((pos < 0) || (pos >= s->length))
		return (0);

	c = *(s->str + pos);
	if ((c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') || (c == 'U')
			|| (c == 'Y'))
		return (1);

	return (0);
}

int slavo_germanic(metastring * s) {
	if ((char *) strstr(s->str, "W"))
		return (1);
	else if ((char *) strstr(s->str, "K"))
		return (1);
	else if ((char *) strstr(s->str, "CZ"))
		return (1);
	else if ((char *) strstr(s->str, "WITZ"))
		return (1);
	else
		return (0);
}

int get_len(metastring * s) {
	return (s->length);
}

char get_at(metastring * s, int pos) {
	if ((pos < 0) || (pos >= s->length))
		return ('\0');

	return ((char) *(s->str + pos));
}

void set_at(metastring * s, int pos, char c) {
	if ((pos < 0) || (pos >= s->length))
		return;

	*(s->str + pos) = c;
}

/*
 Caveats: the START value is 0 based
 */
int str_at(metastring * s, int start, int length, ...) {
	char *test;
	char *pos;
	va_list ap;

	if ((start < 0) || (start >= s->length))
		return (0);

	pos = (s->str + start);
	va_start(ap, length);

	do {
		test = va_arg(ap, char *);
		if (*test && (strncmp(pos, test, length) == 0))
			return (1);
	} while (strcmp(test, ""));

	va_end(ap);

	return (0);
}

void metaph_add(metastring * s, char *new_str) {
	int add_length;

	if (new_str == NULL )
		return;

	add_length = strlen(new_str);
	if ((s->length + add_length) > (s->bufsize - 1)) {
		inc_buffer(s, add_length);
	}

	strcat(s->str, new_str);
	s->length += add_length;
}

void double_metaphone_custom(const char *str, char **codes) {
	int length;
	metastring *original;
	metastring *primary;
	metastring *secondary;
	int current;
	int last;

	current = 0;
	/* we need the real length and last prior to padding */
	length = strlen(str);
	last = length - 1;
	original = new_meta_string(str);
	/* Pad original so we can index beyond end */
	metaph_add(original, "     ");

	primary = new_meta_string("");
	secondary = new_meta_string("");
	primary->free_string_on_destroy = 0;
	secondary->free_string_on_destroy = 0;

	make_upper(original);

	/* skip these when at start of word */
	if (str_at(original, 0, 2, "GN", "KN", "PN", "WR", "PS", ""))
		current += 1;

	/* Initial 'X' is pronounced 'Z' e.g. 'Xavier' */
	if (get_at(original, 0) == 'X') {
		metaph_add(primary, "S"); /* 'Z' maps to 'S' */
		metaph_add(secondary, "S");
		current += 1;
	}

	/* main loop */
	while ((primary->length < 4) || (secondary->length < 4)) {
		if (current >= length)
			break;

		switch (get_at(original, current)) {
		case 'A':
		case 'E':
		case 'I':
		case 'O':
		case 'U':
		case 'Y':
			if (current == 0) {
				/* all init vowels now map to 'A' */
				metaph_add(primary, "A");
				metaph_add(secondary, "A");
			}
			current += 1;
			break;

		case 'B':

			/* "-mb", e.g", "dumb", already skipped over... */
			metaph_add(primary, "P");
			metaph_add(secondary, "P");

			if (get_at(original, current + 1) == 'B')
				current += 2;
			else
				current += 1;
			break;

		case 'Ç':
			metaph_add(primary, "S");
			metaph_add(secondary, "S");
			current += 1;
			break;

		case 'C':
			/* various germanic */
			if ((current > 1) && !is_vowel(original, current - 2)
					&& str_at(original, (current - 1), 3, "ACH", "")
					&& ((get_at(original, current + 2) != 'I')
							&& ((get_at(original, current + 2) != 'E')
									|| str_at(original, (current - 2), 6,
											"BACHER", "MACHER", "")))) {
				metaph_add(primary, "K");
				metaph_add(secondary, "K");
				current += 2;
				break;
			}

			/* special case 'caesar' */
			if ((current == 0)
					&& str_at(original, current, 6, "CAESAR", "")) {
				metaph_add(primary, "S");
				metaph_add(secondary, "S");
				current += 2;
				break;
			}

			/* italian 'chianti' */
			if (str_at(original, current, 4, "CHIA", "")) {
				metaph_add(primary, "K");
				metaph_add(secondary, "K");
				current += 2;
				break;
			}

			if (str_at(original, current, 2, "CH", "")) {
				/* find 'michael' */
				if ((current > 0)
						&& str_at(original, current, 4, "CHAE", "")) {
					metaph_add(primary, "K");
					metaph_add(secondary, "X");
					current += 2;
					break;
				}

				/* greek roots e.g. 'chemistry', 'chorus' */
				if ((current == 0)
						&& (str_at(original, (current + 1), 5, "HARAC",
								"HARIS", "")
								|| str_at(original, (current + 1), 3, "HOR",
										"HYM", "HIA", "HEM", ""))
						&& !str_at(original, 0, 5, "CHORE", "")) {
					metaph_add(primary, "K");
					metaph_add(secondary, "K");
					current += 2;
					break;
				}

				/* germanic, greek, or otherwise 'ch' for 'kh' sound */
				if ((str_at(original, 0, 4, "VAN ", "VON ", "")
						|| str_at(original, 0, 3, "SCH", ""))
						/*  'architect but not 'arch', 'orchestra', 'orchid' */
						|| str_at(original, (current - 2), 6, "ORCHES",
								"ARCHIT", "ORCHID", "")
						|| str_at(original, (current + 2), 1, "T", "S", "")
						|| ((str_at(original, (current - 1), 1, "A", "O", "U",
								"E", "") || (current == 0))
								/* e.g., 'wachtler', 'wechsler', but not 'tichner' */
								&& str_at(original, (current + 2), 1, "L",
										"R", "N", "M", "B", "H", "F", "V", "W",
										" ", ""))) {
					metaph_add(primary, "K");
					metaph_add(secondary, "K");
				} else {
					if (current > 0) {
						if (str_at(original, 0, 2, "MC", "")) {
							/* e.g., "McHugh" */
							metaph_add(primary, "K");
							metaph_add(secondary, "K");
						} else {
							metaph_add(primary, "X");
							metaph_add(secondary, "K");
						}
					} else {
						metaph_add(primary, "X");
						metaph_add(secondary, "X");
					}
				}
				current += 2;
				break;
			}
			/* e.g, 'czerny' */
			if (str_at(original, current, 2, "CZ", "")
					&& !str_at(original, (current - 2), 4, "WICZ", "")) {
				metaph_add(primary, "S");
				metaph_add(secondary, "X");
				current += 2;
				break;
			}

			/* e.g., 'focaccia' */
			if (str_at(original, (current + 1), 3, "CIA", "")) {
				metaph_add(primary, "X");
				metaph_add(secondary, "X");
				current += 3;
				break;
			}

			/* double 'C', but not if e.g. 'McClellan' */
			if (str_at(original, current, 2, "CC", "")
					&& !((current == 1) && (get_at(original, 0) == 'M'))) {
				/* 'bellocchio' but not 'bacchus' */
				if (str_at(original, (current + 2), 1, "I", "E", "H", "")
						&& !str_at(original, (current + 2), 2, "HU", "")) {
					/* 'accident', 'accede' 'succeed' */
					if (((current == 1) && (get_at(original, current - 1) == 'A'))
							|| str_at(original, (current - 1), 5, "UCCEE",
									"UCCES", "")) {
						metaph_add(primary, "KS");
						metaph_add(secondary, "KS");
						/* 'bacci', 'bertucci', other italian */
					} else {
						metaph_add(primary, "X");
						metaph_add(secondary, "X");
					}
					current += 3;
					break;
				} else { /* Pierce's rule */
					metaph_add(primary, "K");
					metaph_add(secondary, "K");
					current += 2;
					break;
				}
			}
			if (str_at(original, current, 2, "CK", "CG", "CQ", "")) {
				metaph_add(primary, "K");
				metaph_add(secondary, "K");
				current += 2;
				break;
			}

			if (str_at(original, current, 2, "CI", "CE", "CY", "")) {
				/* italian vs. english */
				if (str_at(original, current, 3, "CIO", "CIE", "CIA", "")) {
					metaph_add(primary, "S");
					metaph_add(secondary, "X");
				} else {
					metaph_add(primary, "S");
					metaph_add(secondary, "S");
				}
				current += 2;
				break;
			}

			/* else */
			metaph_add(primary, "K");
			metaph_add(secondary, "K");

			/* name sent in 'mac caffrey', 'mac gregor */
			if (str_at(original, (current + 1), 2, " C", " Q", " G", ""))
				current += 3;
			else if (str_at(original, (current + 1), 1, "C", "K", "Q", "")
					&& !str_at(original, (current + 1), 2, "CE", "CI", ""))
				current += 2;
			else
				current += 1;
			break;

		case 'D':
			if (str_at(original, current, 2, "DG", "")) {
				if (str_at(original, (current + 2), 1, "I", "E", "Y", "")) {
					/* e.g. 'edge' */
					metaph_add(primary, "J");
					metaph_add(secondary, "J");
					current += 3;
					break;
				} else {
					/* e.g. 'edgar' */
					metaph_add(primary, "TK");
					metaph_add(secondary, "TK");
					current += 2;
					break;
				}
			}

			if (str_at(original, current, 2, "DT", "DD", "")) {
				metaph_add(primary, "T");
				metaph_add(secondary, "T");
				current += 2;
				break;
			}

			/* else */
			metaph_add(primary, "T");
			metaph_add(secondary, "T");
			current += 1;
			break;

		case 'F':
			if (get_at(original, current + 1) == 'F')
				current += 2;
			else
				current += 1;
			metaph_add(primary, "F");
			metaph_add(secondary, "F");
			break;

		case 'G':
			if (get_at(original, current + 1) == 'H') {
				if ((current > 0) && !is_vowel(original, current - 1)) {
					metaph_add(primary, "K");
					metaph_add(secondary, "K");
					current += 2;
					break;
				}

				if (current < 3) {
					/* 'ghislane', ghiradelli */
					if (current == 0) {
						if (get_at(original, current + 2) == 'I') {
							metaph_add(primary, "J");
							metaph_add(secondary, "J");
						} else {
							metaph_add(primary, "K");
							metaph_add(secondary, "K");
						}
						current += 2;
						break;
					}
				}
				/* Parker's rule (with some further refinements) - e.g., 'hugh' */
				if (((current > 1)
						&& str_at(original, (current - 2), 1, "B", "H", "D",
								""))
						/* e.g., 'bough' */
						|| ((current > 2)
								&& str_at(original, (current - 3), 1, "B",
										"H", "D", ""))
						/* e.g., 'broughton' */
						|| ((current > 3)
								&& str_at(original, (current - 4), 1, "B",
										"H", ""))) {
					current += 2;
					break;
				} else {
					/* e.g., 'laugh', 'McLaughlin', 'cough', 'gough', 'rough', 'tough' */
					if ((current > 2) && (get_at(original, current - 1) == 'U')
							&& str_at(original, (current - 3), 1, "C", "G",
									"L", "R", "T", "")) {
						metaph_add(primary, "F");
						metaph_add(secondary, "F");
					} else if ((current > 0)
							&& get_at(original, current - 1) != 'I') {

						metaph_add(primary, "K");
						metaph_add(secondary, "K");
					}

					current += 2;
					break;
				}
			}

			if (get_at(original, current + 1) == 'N') {
				if ((current == 1) && is_vowel(original, 0)
						&& !slavo_germanic(original)) {
					metaph_add(primary, "KN");
					metaph_add(secondary, "N");
				} else
				/* not e.g. 'cagney' */
				if (!str_at(original, (current + 2), 2, "EY", "")
						&& (get_at(original, current + 1) != 'Y')
						&& !slavo_germanic(original)) {
					metaph_add(primary, "N");
					metaph_add(secondary, "KN");
				} else {
					metaph_add(primary, "KN");
					metaph_add(secondary, "KN");
				}
				current += 2;
				break;
			}

			/* 'tagliaro' */
			if (str_at(original, (current + 1), 2, "LI", "")
					&& !slavo_germanic(original)) {
				metaph_add(primary, "KL");
				metaph_add(secondary, "L");
				current += 2;
				break;
			}

			/* -ges-,-gep-,-gel-, -gie- at beginning */
			if ((current == 0)
					&& ((get_at(original, current + 1) == 'Y')
							|| str_at(original, (current + 1), 2, "ES", "EP",
									"EB", "EL", "EY", "IB", "IL", "IN", "IE",
									"EI", "ER", ""))) {
				metaph_add(primary, "K");
				metaph_add(secondary, "J");
				current += 2;
				break;
			}

			/*  -ger-,  -gy- */
			if ((str_at(original, (current + 1), 2, "ER", "")
					|| (get_at(original, current + 1) == 'Y'))
					&& !str_at(original, 0, 6, "DANGER", "RANGER", "MANGER",
							"")
					&& !str_at(original, (current - 1), 1, "E", "I", "")
					&& !str_at(original, (current - 1), 3, "RGY", "OGY",
							"")) {
				metaph_add(primary, "K");
				metaph_add(secondary, "J");
				current += 2;
				break;
			}

			/*  italian e.g, 'biaggi' */
			if (str_at(original, (current + 1), 1, "E", "I", "Y", "")
					|| str_at(original, (current - 1), 4, "AGGI", "OGGI",
							"")) {
				/* obvious germanic */
				if ((str_at(original, 0, 4, "VAN ", "VON ", "")
						|| str_at(original, 0, 3, "SCH", ""))
						|| str_at(original, (current + 1), 2, "ET", "")) {
					metaph_add(primary, "K");
					metaph_add(secondary, "K");
				} else {
					/* always soft if french ending */
					if (str_at(original, (current + 1), 4, "IER ", "")) {
						metaph_add(primary, "J");
						metaph_add(secondary, "J");
					} else {
						metaph_add(primary, "J");
						metaph_add(secondary, "K");
					}
				}
				current += 2;
				break;
			}

			if (get_at(original, current + 1) == 'G')
				current += 2;
			else
				current += 1;
			metaph_add(primary, "K");
			metaph_add(secondary, "K");
			break;

		case 'H':
			/* only keep if first & before vowel or btw. 2 vowels */
			if (((current == 0) || is_vowel(original, current - 1))
					&& is_vowel(original, current + 1)) {
				metaph_add(primary, "H");
				metaph_add(secondary, "H");
				current += 2;
			} else
				/* also takes care of 'HH' */
				current += 1;
			break;

		case 'J':
			/* obvious spanish, 'jose', 'san jacinto' */
			if (str_at(original, current, 4, "JOSE", "")
					|| str_at(original, 0, 4, "SAN ", "")) {
				if (((current == 0) && (get_at(original, current + 4) == ' '))
						|| str_at(original, 0, 4, "SAN ", "")) {
					metaph_add(primary, "H");
					metaph_add(secondary, "H");
				} else {
					metaph_add(primary, "J");
					metaph_add(secondary, "H");
				}
				current += 1;
				break;
			}

			if ((current == 0) && !str_at(original, current, 4, "JOSE", "")) {
				metaph_add(primary, "J"); /* Yankelovich/Jankelowicz */
				metaph_add(secondary, "A");
			} else {
				/* spanish pron. of e.g. 'bajador' */
				if (is_vowel(original, current - 1) && !slavo_germanic(original)
						&& ((get_at(original, current + 1) == 'A')
								|| (get_at(original, current + 1) == 'O'))) {
					metaph_add(primary, "J");
					metaph_add(secondary, "H");
				} else {
					if (current == last) {
						metaph_add(primary, "J");
						metaph_add(secondary, "");
					} else {
						if (!str_at(original, (current + 1), 1, "L", "T", "K",
								"S", "N", "M", "B", "Z", "")
								&& !str_at(original, (current - 1), 1, "S",
										"K", "L", "")) {
							metaph_add(primary, "J");
							metaph_add(secondary, "J");
						}
					}
				}
			}

			if (get_at(original, current + 1) == 'J') /* it could happen! */
				current += 2;
			else
				current += 1;
			break;

		case 'K':
			if (get_at(original, current + 1) == 'K')
				current += 2;
			else
				current += 1;
			metaph_add(primary, "K");
			metaph_add(secondary, "K");
			break;

		case 'L':
			if (get_at(original, current + 1) == 'L') {
				/* spanish e.g. 'cabrillo', 'gallegos' */
				if (((current == (length - 3))
						&& str_at(original, (current - 1), 4, "ILLO", "ILLA",
								"ALLE", ""))
						|| ((str_at(original, (last - 1), 2, "AS", "OS", "")
								|| str_at(original, last, 1, "A", "O", ""))
								&& str_at(original, (current - 1), 4, "ALLE",
										""))) {
					metaph_add(primary, "L");
					metaph_add(secondary, "");
					current += 2;
					break;
				}
				current += 2;
			} else
				current += 1;
			metaph_add(primary, "L");
			metaph_add(secondary, "L");
			break;

		case 'M':
			if ((str_at(original, (current - 1), 3, "UMB", "")
					&& (((current + 1) == last)
							|| str_at(original, (current + 2), 2, "ER", "")))
			/* 'dumb','thumb' */
			|| (get_at(original, current + 1) == 'M'))
				current += 2;
			else
				current += 1;
			metaph_add(primary, "M");
			metaph_add(secondary, "M");
			break;

		case 'N':
			if (get_at(original, current + 1) == 'N')
				current += 2;
			else
				current += 1;
			metaph_add(primary, "N");
			metaph_add(secondary, "N");
			break;

		case 'Ñ':
			current += 1;
			metaph_add(primary, "N");
			metaph_add(secondary, "N");
			break;

		case 'P':
			if (get_at(original, current + 1) == 'H') {
				metaph_add(primary, "F");
				metaph_add(secondary, "F");
				current += 2;
				break;
			}

			/* also account for "campbell", "raspberry" */
			if (str_at(original, (current + 1), 1, "P", "B", ""))
				current += 2;
			else
				current += 1;
			metaph_add(primary, "P");
			metaph_add(secondary, "P");
			break;

		case 'Q':
			if (get_at(original, current + 1) == 'Q')
				current += 2;
			else
				current += 1;
			metaph_add(primary, "K");
			metaph_add(secondary, "K");
			break;

		case 'R':
			/* french e.g. 'rogier', but exclude 'hochmeier' */
			if ((current == last) && !slavo_germanic(original)
					&& str_at(original, (current - 2), 2, "IE", "")
					&& !str_at(original, (current - 4), 2, "ME", "MA", "")) {
				metaph_add(primary, "");
				metaph_add(secondary, "R");
			} else {
				metaph_add(primary, "R");
				metaph_add(secondary, "R");
			}

			if (get_at(original, current + 1) == 'R')
				current += 2;
			else
				current += 1;
			break;

		case 'S':
			/* special cases 'island', 'isle', 'carlisle', 'carlysle' */
			if (str_at(original, (current - 1), 3, "ISL", "YSL", "")) {
				current += 1;
				break;
			}

			/* special case 'sugar-' */
			if ((current == 0) && str_at(original, current, 5, "SUGAR", "")) {
				metaph_add(primary, "X");
				metaph_add(secondary, "S");
				current += 1;
				break;
			}

			if (str_at(original, current, 2, "SH", "")) {
				/* germanic */
				if (str_at(original, (current + 1), 4, "HEIM", "HOEK", "HOLM",
						"HOLZ", "")) {
					metaph_add(primary, "S");
					metaph_add(secondary, "S");
				} else {
					metaph_add(primary, "X");
					metaph_add(secondary, "X");
				}
				current += 2;
				break;
			}

			/* italian & armenian */
			if (str_at(original, current, 3, "SIO", "SIA", "")
					|| str_at(original, current, 4, "SIAN", "")) {
				if (!slavo_germanic(original)) {
					metaph_add(primary, "S");
					metaph_add(secondary, "X");
				} else {
					metaph_add(primary, "S");
					metaph_add(secondary, "S");
				}
				current += 3;
				break;
			}

			/* german & anglicisations, e.g. 'smith' match 'schmidt', 'snider' match 'schneider'
			 also, -sz- in slavic language altho in hungarian it is pronounced 's' */
			if (((current == 0)
					&& str_at(original, (current + 1), 1, "M", "N", "L", "W",
							""))
					|| str_at(original, (current + 1), 1, "Z", "")) {
				metaph_add(primary, "S");
				metaph_add(secondary, "X");
				if (str_at(original, (current + 1), 1, "Z", ""))
					current += 2;
				else
					current += 1;
				break;
			}

			if (str_at(original, current, 2, "SC", "")) {
				/* Schlesinger's rule */
				if (get_at(original, current + 2) == 'H') {
					/* dutch origin, e.g. 'school', 'schooner' */
					if (str_at(original, (current + 3), 2, "OO", "ER", "EN",
							"UY", "ED", "EM", "")) {
						/* 'schermerhorn', 'schenker' */
						if (str_at(original, (current + 3), 2, "ER", "EN",
								"")) {
							metaph_add(primary, "X");
							metaph_add(secondary, "SK");
						} else {
							metaph_add(primary, "SK");
							metaph_add(secondary, "SK");
						}
						current += 3;
						break;
					} else {
						if ((current == 0) && !is_vowel(original, 3)
								&& (get_at(original, 3) != 'W')) {
							metaph_add(primary, "X");
							metaph_add(secondary, "S");
						} else {
							metaph_add(primary, "X");
							metaph_add(secondary, "X");
						}
						current += 3;
						break;
					}
				}
				if (str_at(original, (current + 2), 1, "I", "E", "Y", "")) {
					metaph_add(primary, "S");
					metaph_add(secondary, "S");
					current += 3;
					break;
				}
				/* else */
				metaph_add(primary, "SK");
				metaph_add(secondary, "SK");
				current += 3;
				break;
			}

			/* french e.g. 'resnais', 'artois' */
			if ((current == last)
					&& str_at(original, (current - 2), 2, "AI", "OI", "")) {
				metaph_add(primary, "");
				metaph_add(secondary, "S");
			} else {
				metaph_add(primary, "S");
				metaph_add(secondary, "S");
			}

			if (str_at(original, (current + 1), 1, "S", "Z", ""))
				current += 2;
			else
				current += 1;
			break;

		case 'T':
			if (str_at(original, current, 4, "TION", "")) {
				metaph_add(primary, "X");
				metaph_add(secondary, "X");
				current += 3;
				break;
			}

			if (str_at(original, current, 3, "TIA", "TCH", "")) {
				metaph_add(primary, "X");
				metaph_add(secondary, "X");
				current += 3;
				break;
			}

			if (str_at(original, current, 2, "TH", "")
					|| str_at(original, current, 3, "TTH", "")) {
				/* special case 'thomas', 'thames' or germanic */
				if (str_at(original, (current + 2), 2, "OM", "AM", "")
						|| str_at(original, 0, 4, "VAN ", "VON ", "")
						|| str_at(original, 0, 3, "SCH", "")) {
					metaph_add(primary, "T");
					metaph_add(secondary, "T");
				} else {
					metaph_add(primary, "0"); /* yes, zero */
					metaph_add(secondary, "T");
				}
				current += 2;
				break;
			}

			if (str_at(original, (current + 1), 1, "T", "D", ""))
				current += 2;
			else
				current += 1;
			metaph_add(primary, "T");
			metaph_add(secondary, "T");
			break;

		case 'V':
			if (get_at(original, current + 1) == 'V')
				current += 2;
			else
				current += 1;
			metaph_add(primary, "F");
			metaph_add(secondary, "F");
			break;

		case 'W':
			/* can also be in middle of word */
			if (str_at(original, current, 2, "WR", "")) {
				metaph_add(primary, "R");
				metaph_add(secondary, "R");
				current += 2;
				break;
			}

			if ((current == 0)
					&& (is_vowel(original, current + 1)
							|| str_at(original, current, 2, "WH", ""))) {
				/* Wasserman should match Vasserman */
				if (is_vowel(original, current + 1)) {
					metaph_add(primary, "A");
					metaph_add(secondary, "F");
				} else {
					/* need Uomo to match Womo */
					metaph_add(primary, "A");
					metaph_add(secondary, "A");
				}
			}

			/* Arnow should match Arnoff */
			if (((current == last) && is_vowel(original, current - 1))
					|| str_at(original, (current - 1), 5, "EWSKI", "EWSKY",
							"OWSKI", "OWSKY", "")
					|| str_at(original, 0, 3, "SCH", "")) {
				metaph_add(primary, "");
				metaph_add(secondary, "F");
				current += 1;
				break;
			}

			/* polish e.g. 'filipowicz' */
			if (str_at(original, current, 4, "WICZ", "WITZ", "")) {
				metaph_add(primary, "TS");
				metaph_add(secondary, "FX");
				current += 4;
				break;
			}

			/* else skip it */
			current += 1;
			break;

		case 'X':
			/* french e.g. breaux */
			if (!((current == last)
					&& (str_at(original, (current - 3), 3, "IAU", "EAU", "")
							|| str_at(original, (current - 2), 2, "AU", "OU",
									"")))) {
				metaph_add(primary, "KS");
				metaph_add(secondary, "KS");
			}

			if (str_at(original, (current + 1), 1, "C", "X", ""))
				current += 2;
			else
				current += 1;
			break;

		case 'Z':
			/* chinese pinyin e.g. 'zhao' */
			if (get_at(original, current + 1) == 'H') {
				metaph_add(primary, "J");
				metaph_add(secondary, "J");
				current += 2;
				break;
			} else if (str_at(original, (current + 1), 2, "ZO", "ZI", "ZA",
					"")
					|| (slavo_germanic(original)
							&& ((current > 0)
									&& get_at(original, current - 1) != 'T'))) {
				metaph_add(primary, "S");
				metaph_add(secondary, "TS");
			} else {
				metaph_add(primary, "S");
				metaph_add(secondary, "S");
			}

			if (get_at(original, current + 1) == 'Z')
				current += 2;
			else
				current += 1;
			break;

		default:
			current += 1;
			break;
		}
		/* printf("PRIMARY: %s\n", primary->str);
		 printf("SECONDARY: %s\n", secondary->str);  */
	}

	if (primary->length > 4)
		set_at(primary, 4, '\0');

	if (secondary->length > 4)
		set_at(secondary, 4, '\0');

	*codes = primary->str;
	*++codes = secondary->str;

	free_meta_string(original);
	free_meta_string(primary);
	free_meta_string(secondary);

}

char *double_metaphone(const char *str) {

	char *code = malloc(MAX_MLEN * sizeof(char));
	code[0] = '\0';
	double_metaphone_custom(str, &code);
	return (code);

}

float double_metaphone_similarity(const char *str1, const char *str2) {

	char *s1 = double_metaphone(str1);
	char *s2 = double_metaphone(str2);
	float res = smith_waterman_gotoh_similarity(s1, s2);
	free(s1);
	free(s2);

	return (res);

}
