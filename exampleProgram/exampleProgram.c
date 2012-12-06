#include <stdlib.h>
#include <string.h>
#include "uthash.h"
#include "utlist.h"
#include "cost.h"
#include "tokenizer.h"
#include "block_distance.h"

int main(void) {

	const char *str1 = "aaa BBB ccc DDD eee FFF ggg";
	const char *str2 = "AAA bbb CCC ddd EEE fff GGG";
	int x;

	cost_t cost = {
			.max_cost = 0,
			.min_cost = 0,
			.gap_cost = 0,
			.tok_str = WHITESPACE_DELIMITERS
	};

	for(x = 0; x < 100000; x++) {
		block_distance_custom(str1, str2, &cost);
	}

	return EXIT_SUCCESS;

}
