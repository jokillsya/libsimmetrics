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

#include "soundex.h"
#include "jaro.h"
#include "cost.h"
#include "util.h"
#include "levenshtein.h"
#include "jaro_winkler.h"
#include "smith_waterman.h"
#include "smith_waterman_gotoh.h"
#include "needleman_wunch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	float x;
	x = needleman_wunch_similarity("Walter BockWalter BockWalter BockWalter BockWalter BockWalter BockWalter BockWalter BockWalter BockWalter Bock", "Walter BokWalter BokWalter BokWalter BokWalter BokWalter BokWalter BokWalter BokWalter BokWalter Bok");
	printf("%f\n", x);
	return 0;
}
