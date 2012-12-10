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

int main(void) {

	const char *str1 = "aaa BBB ccc DDD eee FFF ggg";
	const char *str2 = "AAA bbb CCC ddd EEE fff GGG";
	int x;
		//printf("%f\n", cosine_similarity(str1, str2));
	for(x = 0; x < 1000000; x++)
		cosine_similarity(str1, str2);
	return EXIT_SUCCESS;

}
