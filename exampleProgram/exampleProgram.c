#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "utlist.h"
#include "utarray.h"
#include "uthash.h"
#include "tokenizer.h"
#include "qgrams_distance.h"

int main(void)
{

	int i;
	const char *str1 = "Johnathan2";
	const char *str2 = "Johnathan1";

	printf("D :: %f\n", qgrams_distance_similarity(str1, str2));

	return EXIT_SUCCESS;

}
