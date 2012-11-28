/*
 * cost.h
 *
 *  Created on: 20 Nov 2012
 *      Author: johnathan
 */

#ifndef COST_H_
#define COST_H_

#include <stddef.h>

#define CHR_MIS_SCORE (float)-3
#define CHR_EXT_SCORE (float)5
#define CHR_APR_SCORE (float)3

#define WHITESPACE_DELIMITERS "\r\n\t \u00A0"

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
	char *tok_str; //In case a tokenizer is used in the metric
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
