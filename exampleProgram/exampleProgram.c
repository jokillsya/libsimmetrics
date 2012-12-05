/*
 ============================================================================
 Name        : exampleProgram.c
 Author      : Johnathan Botha
 Version     :
 Copyright   : Copyright - Johnathan Botha <jokillsya@gmail.com>
 Description : Uses shared library to print greeting
               To run the resulting executable the LD_LIBRARY_PATH must be
               set to ${project_loc}/libsimmetrics/.libs
               Alternatively, libtool creates a wrapper shell script in the
               build directory of this program which can be used to run it.
               Here the script will be called exampleProgram.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "cost.h"
#include "soundex.h"
#include "jaro.h"
#include "util.h"
#include "levenshtein.h"
#include "jaro_winkler.h"
#include "smith_waterman.h"
#include "smith_waterman_gotoh.h"
#include "needleman_wunch.h"
#include "simmetrics.h"
#include "monge_elkan.h"
#include "uthash.h"
#include "tokenizer.h"

int main(void) {


	const char *str = "hgf jkl ret jkl asdf gh piet jkl piet pompies piet";

	tokenizer_t *tokens = NULL;
	tokenizer_t *s;

	tokens = uq_tokenize_hash(str, WHITESPACE_DELIMITERS);

	for(s = tokens; s != NULL; s = s->hh.next) {

		printf("H: %d, V: %s\n", s->key, s->value);

	}

	tokenizer_free(tokens);

	return 0;
}
