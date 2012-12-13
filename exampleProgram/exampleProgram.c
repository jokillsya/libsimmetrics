#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "utlist.h"
#include "utarray.h"
#include "uthash.h"
#include "tokenizer.h"
#include "qgrams_distance.h"

int main(void) {

	int i;
	const char *str1 = "aaa BBB ccc DDD eee FFF ggg";
	const char *str2 = "AAA bbb CCC ddd EEE fff GGG";

	for (i = 0; i < 1000000; i++) {

		qgrams_distance_similarity(str1, str2);

	}
	return EXIT_SUCCESS;

}
