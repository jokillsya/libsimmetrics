#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "uthash.h"
#include "utarray.h"
#include "utlist.h"
#include "cost.h"
#include "tokenizer.h"
#include "block_distance.h"
#include "euclidean_distance.h"
#include "cosine_similarity.h"
#include "jaccard_similarity.h"
#include "matching_coefficient.h"

int main(void) {

	const char *str1 = "Test String1";
	const char *str2 = "Test String2";
	const float res = matching_coefficient_similarity(str1, str2);
	printf("%f\n", res);
	return EXIT_SUCCESS;

}
