#include <stdlib.h>
#include <string.h>
#include "uthash.h"
#include "utarray.h"
#include "utlist.h"
#include "cost.h"
#include "tokenizer.h"
#include "block_distance.h"
#include "euclidean_distance.h"
#include "cosine_similarity.h"
#include "jaccard_similarity.h"

int main(void) {

	const char *str1 = "Test String1";
	const char *str2 = "Test String2";
	int x;
		printf("%f\n", jaccard_similarity(str1, str2));
	//for(x = 0; x < 1000000; x++)
	//	jaccard_similarity(str1, str2);
	return EXIT_SUCCESS;

}
