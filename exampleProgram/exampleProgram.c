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

int main(void) {

	//printf("%s",strtok("lsadkjfhldkjf\nalskfdhaaskldfg\taklshdfg\ralksdgf","\t"));

	const char *str1 = "aaa BBB ccc DDD eee FFF";
	const char *str2 = "AAA bbb CCC ddd EEE fff";

	float x;

	comp_idx_cost_t comp_cost = {
			.gap_cost = affine_gap_5_1(),
			.sub_cost = sub_cost_5_3_min_3()
	};

	comp_cost.sub_cost->cost->tok_str = WHITESPACE_DELIMITERS;

	w_comp_idx_cost_t conf = {
			.win_size = 100,
			.comp_conf = &comp_cost
	};

	metric_function_t metric_func;
	metric_func.custom_metric_func = &custom_smith_waterman_gotoh_similarity;

	x = custom_monge_elkan(str1, str2, &metric_func, &conf, WIN_COMP_IDX_COST);
	printf("%f\n", x);
	return 0;
}
