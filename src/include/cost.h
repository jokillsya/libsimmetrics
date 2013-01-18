/*
 * * Copyright (C) 2012 Johnathan Botha et al. All rights reserved.
 *
 * This file is part of libsimmetrics
 *
 * libsimmetrics is the C port of the Java project called Simmetrics,
 *
 * The Java code can be found here: https://github.com/Simmetrics/simmetrics
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * cost.h
 *
 *  Created on: 20 Nov 2012
 *      Author: Johnathan Botha <jokillsya@gmail.com>
 */

#ifndef COST_H_
#define COST_H_

#include <stddef.h>

#define CHR_MIS_SCORE (float)-3
#define CHR_EXT_SCORE (float)5
#define CHR_APR_SCORE (float)3

typedef enum {
	COST,
	SUB_COST,
	AFFINE_COST,
	AFFINE_IDX_COST,
	COMP_COST,
	COMP_IDX_COST,
	WIN_COMP_IDX_COST
} cost_type_e;

typedef struct {
	float max_cost;
	float min_cost;
	float gap_cost; //Provided in case a metric needs it...
} cost_t;

typedef struct {

	cost_t *cost;
	float (*cost_func)(const char *, const int, const char *, const int);

} sub_cost_t;

typedef struct {

	cost_t *cost;
	float (*cost_func)(const char *, const int, const int);

} affine_cost_t;

typedef struct {

	cost_t *cost;
	float (*cost_func) (const int, const int);

} affine_idx_cost_t;

typedef struct {

	affine_idx_cost_t *gap_cost;
	sub_cost_t *sub_cost;

} comp_idx_cost_t;

typedef struct {

	affine_cost_t *gap_cost;
	sub_cost_t *sub_cost;

} comp_cost_t;

typedef struct {

	size_t win_size;
	comp_idx_cost_t *comp_conf;

} w_comp_idx_cost_t;

affine_idx_cost_t* affine_gap_1_over_3();
affine_idx_cost_t* affine_gap_5_1();
sub_cost_t* sub_cost_1();
sub_cost_t* sub_cost_1_min_2();
sub_cost_t* sub_cost_5_3_min_3();

const cost_t *extract_cost(const void *v_conf, cost_type_e cost_type);

void free_affine_sub_cost(affine_idx_cost_t *cost);
void free_sub_cost(sub_cost_t *cost);

#endif /* COST_H_ */
