#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "uthash.h"
#include "utarray.h"
#include "utlist.h"
#include "cost.h"
#include "tokenizer.h"
#include "overlap_coefficient.h"

int main(void) {

	const char *str1 = "Test String1";
	const char *str2 = "Test String2";
	const float res = overlap_coefficient_similarity(str1, str2);
	printf("%f\n", res);
	return EXIT_SUCCESS;

}
