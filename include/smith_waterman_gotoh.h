/*
 * smith_waterman_gotoh.h
 *
 *  Created on: 22 Nov 2012
 *      Author: johnathan
 */

#ifndef SMITH_WATERMAN_GOTOH_H_
#define SMITH_WATERMAN_GOTOH_H_

float custom_smith_waterman_gotoh(const char *str1, const char *str2, const w_comp_idx_cost_t *conf);
float smith_waterman_gotoh(const char *str1, const char *str2);
float custom_smith_waterman_gotoh_similarity(const char *str1, const char *str2, const void *v_conf);
float smith_waterman_gotoh_similarity(const char *str1, const char *str2);

#endif /* SMITH_WATERMAN_GOTOH_H_ */
