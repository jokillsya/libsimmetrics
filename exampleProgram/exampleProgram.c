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
	int i;
#pragma omp for
	for(i = 0; i < 100000; i++)
		monge_elkan_similarity(str1, str2);
	//printf("%f\n", x);
	return 0;
}
