/*
 * smith_waterman.h
 *
 *  Created on: 21 Nov 2012
 *      Author: johnathan
 */

#ifndef SMITH_WATERMAN_H_
#define SMITH_WATERMAN_H_

float smith_waterman(const char *str1, const char *str2);
float custom_smith_waterman(const char *str1, const char *str2, sub_cost_t cost_s);
float custom_smith_waterman_similarity(const char *str1, const char *str2, sub_cost_t sub_cost);
float smith_waterman_similarity(const char *str1, const char *str2);

#endif /* SMITH_WATERMAN_H_ */
