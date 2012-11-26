/*
 * smith_waterman_gotoh.h
 *
 *  Created on: 22 Nov 2012
 *      Author: johnathan
 */

#ifndef SMITH_WATERMAN_GOTOH_H_
#define SMITH_WATERMAN_GOTOH_H_

#include <stddef.h>

typedef struct {

	size_t win_size;
	affine_idx_cost_t gap_cost;
	sub_cost_t sub_cost;

} sw_gotoh_t;

float custom_smith_waterman_gotoh(const char *str1, const char *str2, sw_gotoh_t conf);
float smith_waterman_gotoh(const char *str1, const char *str2);
float custom_smith_waterman_gotoh_similarity(const char *str1, const char *str2, sw_gotoh_t conf);
float smith_waterman_gotoh_similarity(const char *str1, const char *str2);

#endif /* SMITH_WATERMAN_GOTOH_H_ */
