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
 * tokenizer.c
 *
 *  Created on: 05 Dec 2012
 *      Author: Johnathan Botha <jokillsya@gmail.com>
 */

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cost.h"
#include "uthash.h"
#include "utlist.h"
#include "utarray.h"
#include "tokenizer.h"

static unsigned int str_hash(const char *s) {

    unsigned int hash = 0;
    int c;

    while((c = *s++))
    {
        /* hash = hash * 33 ^ c */
        hash = ((hash << 5) + hash) ^ c;
    }

    return (hash);

}

dl_token_t *tokenize_to_dllist(const char *str, const char *delimiters) {

	dl_token_t *el;
	dl_token_t *r = NULL;

	char *tok;
	char tmp[strlen(str) + 1];
	strcpy(tmp, str);

	tok = strtok(tmp, delimiters);

	while(tok != NULL) {

		el = malloc(sizeof(dl_token_t));
		el->token = strdup(tok);
		DL_APPEND(r, el);
		tok = strtok(NULL, delimiters);

	}

	return (r);

}

/**
 * This function will return NULL if the qgram_t struct contains invalid values
 */
dl_token_t *qgram_tokenize_to_dllist(const char *str, const qgram_t *qtype) {

	int i;
	int init_len = strlen(str) + 1;
	char *tmp;

	//Mem corruption will occur otherwise...
	if(qtype->qgram_len < 1 || qtype->qgram_len > 3)
		return NULL;

	if(qtype->extended) {

		tmp = calloc((init_len + qtype->qgram_len), sizeof(char));

		for(i = 0; i < (qtype->qgram_len - 1); i++)
			strcat(tmp, QGRAM_SP);

		strcat(tmp, str);

		for(i = 0; i < (qtype->qgram_len - 1); i++)
			strcat(tmp, QGRAM_EP);

	} else {

		tmp = calloc(init_len, sizeof(char));
		strcpy(tmp, str);

	}

	dl_token_t *el;
	dl_token_t *r = NULL;

	int cp = 0;
	int len = strlen(tmp) - qtype->qgram_len + 1;
	char *t_ptr;

	while(cp < len) {

		t_ptr = (char *)&tmp[cp];
		el = malloc(sizeof(dl_token_t));
		//Allocate all chars - plus terminator...
		el->token = calloc((qtype->qgram_len + 1), sizeof(char));
		//Copy bytes safely - strncpy should append the \0
		strncpy(el->token, t_ptr, (sizeof(char) * qtype->qgram_len));
		DL_APPEND(r, el);
		cp++;
	}

	free(tmp);

	return (r);

}

hash_token_t *qgram_uq_tokenize_to_hash(const char *str, const qgram_t *qtype) {

	int i;
	int init_len = strlen(str) + 1;
	unsigned int hash;
	char *tmp;

	//Mem corruption will occur otherwise...
	if(qtype->qgram_len < 1 || qtype->qgram_len > 3)
		return NULL;

	if(qtype->extended) {

		tmp = calloc((init_len + qtype->qgram_len), sizeof(char));

		for(i = 0; i < (qtype->qgram_len - 1); i++)
			strcat(tmp, QGRAM_SP);

		strcat(tmp, str);

		for(i = 0; i < (qtype->qgram_len - 1); i++)
			strcat(tmp, QGRAM_EP);

	} else {

		tmp = calloc(init_len, sizeof(char));
		strcpy(tmp, str);

	}

	hash_token_t *s, *table = NULL;

	int cp = 0;
	int len = strlen(tmp) - qtype->qgram_len + 1;
	char *t_ptr, *hchk;

	while(cp < len) {

		t_ptr = (char *)&tmp[cp];
		//Allocate all chars - plus terminator...
		hchk = calloc((qtype->qgram_len + 1), sizeof(char));
		//Copy bytes safely - strncpy should append the \0
		strncpy(hchk, t_ptr, (sizeof(char) * qtype->qgram_len));

		hash = str_hash(hchk);

		HASH_FIND_INT(table, &hash, s);

		if(s == NULL) {

			s = malloc(sizeof(hash_token_t));
			s->key = hash;
			s->value = strdup(hchk);
			HASH_ADD_INT(table, key, s);

		}

		free(hchk);

		cp++;

	}

	free(tmp);

	return (table);

}

UT_array *qgram_tokenize_to_utarray(const char *str, const qgram_t *qtype) {

	int i;
	int init_len = strlen(str) + 1;
	char *tmp;

	//Mem corruption will occur otherwise...
	if(qtype->qgram_len < 1 || qtype->qgram_len > 3)
		return NULL;

	if(qtype->extended) {

		tmp = calloc((init_len + qtype->qgram_len), sizeof(char));

		for(i = 0; i < (qtype->qgram_len - 1); i++)
			strcat(tmp, QGRAM_SP);

		strcat(tmp, str);

		for(i = 0; i < (qtype->qgram_len - 1); i++)
			strcat(tmp, QGRAM_EP);

	} else {

		tmp = calloc(init_len, sizeof(char));
		strcpy(tmp, str);

	}

	UT_array *strs;
	utarray_new(strs, &ut_str_icd);

	int cp = 0;
	int len = strlen(tmp) - qtype->qgram_len + 1;
	char *t_ptr, *el;

	while(cp < len) {

		t_ptr = (char *)&tmp[cp];
		//Allocate all chars - plus terminator...
		el = calloc((qtype->qgram_len + 1), sizeof(char));
		//Copy bytes safely - strncpy should append the \0
		strncpy(el, t_ptr, (sizeof(char) * qtype->qgram_len));

		utarray_push_back(strs, &el);

		free(el);

		cp++;
	}

	free(tmp);

	return (strs);

}

hash_token_t *uq_tokenize_to_hash(const char *str, const char *delimiters) {

	unsigned int hash;
	hash_token_t *s, *table = NULL;
	char *tok;
	char tmp[strlen(str) + 1];
	strcpy(tmp, str);

	tok = strtok(tmp, delimiters);

	while(tok != NULL) {

		hash = str_hash(tok);

		HASH_FIND_INT(table, &hash, s);

		if(s == NULL) {

			s = malloc(sizeof(hash_token_t));
			s->key = str_hash(tok);
			s->value = strdup(tok);
			HASH_ADD_INT(table, key, s);

		}

		tok = strtok(NULL, delimiters);

	}

	return (table);

}

hash_token_t *merge_tokens(hash_token_t *t1, hash_token_t *t2) {

	hash_token_t *res = NULL, *s, *tmp;

	for(s = t1; s != NULL; s = s->hh.next) {

		HASH_FIND_INT(res, &s->key, tmp);

		if(tmp == NULL) {

			tmp = malloc(sizeof(hash_token_t));
			tmp->key = s->key;
			tmp->value = strdup(s->value);
			HASH_ADD_INT(res, key, tmp);

		}

	}

	for(s = t2; s != NULL; s = s->hh.next) {

		HASH_FIND_INT(res, &s->key, tmp);

		if(tmp == NULL) {

			tmp = malloc(sizeof(hash_token_t));
			tmp->key = s->key;
			tmp->value = strdup(s->value);
			HASH_ADD_INT(res, key, tmp);

		}

	}

	return (res);

}

UT_array *tokenize_to_utarray(const char *str, const char *delimiters) {

	UT_array *strs;

	char *tok;
	char tmp[strlen(str) + 1];
	strcpy(tmp, str);

	utarray_new(strs, &ut_str_icd);

	tok = strtok(tmp, delimiters);

	while(tok != NULL) {

		utarray_push_back(strs, &tok);
		tok = strtok(NULL, delimiters);

	}

	return (strs);

}

void hash_token_free(hash_token_t *table) {

	hash_token_t *s, *tmp;

	HASH_ITER(hh, table, s, tmp) {

		HASH_DEL(table, s);
		free(s->value);
		free(s);

	}

}

void dll_token_free(dl_token_t *head) {

	dl_token_t *elt, *tmp;

	DL_FOREACH_SAFE(head, elt, tmp) {
		LL_DELETE(head, elt);
		free(elt->token);
		free(elt);
	}

}


