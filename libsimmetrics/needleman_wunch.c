/*
 * needleman_wunch.c
 *
 *  Created on: 23 Nov 2012
 *      Author: johnathan
 */
#include <stdlib.h>
#include <string.h>
#include "cost.h"
#include "util.h"

float custom_needleman_wunch(const char *str1, const char *str2, sub_cost_t conf) {

	int n = strlen(str1);
	int m = strlen(str2);

	int i, j;
	float cost;

	if((n == 0) || (m == 0)) {
		return 0;
	}

	float d[n + 1][m + 1];

	for(i = 0; i <= n; i++)
		d[i][0] = i;

	for(j = 0; j <= m; j++)
		d[0][j] = j;

	for(i = 1; i <= n; i++) {

		for(j = 1; j <= m; j++) {

			cost = conf.cost_func(str1, i - 1, str2, j - 1);
			d[i][j] = MIN3(d[i - 1][j] + conf.cost.gap_cost, d[i][j - 1] + conf.cost.gap_cost, d[i - 1][j - 1] + cost);

		}

	}

	return d[n][m];

}


