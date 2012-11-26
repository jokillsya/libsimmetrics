/*
 * cost.h
 *
 *  Created on: 20 Nov 2012
 *      Author: johnathan
 */

#ifndef COST_H_
#define COST_H_

#define CHR_MIS_SCORE (float)-3
#define CHR_EXT_SCORE (float)5
#define CHR_APR_SCORE (float)3

typedef struct {
	float max_cost;
	float min_cost;
	float gap_cost; //Provided in case a metric needs it...
} cost_t;

typedef struct {

	cost_t cost;
	float (*cost_func)(const char *, const int, const char *, const int);

} sub_cost_t;

typedef struct {

	cost_t cost;
	float (*cost_func)(const char *, const int, const int);

} affine_cost_t;

typedef struct {

	cost_t cost;
	float (*cost_func) (const int, const int);

} affine_idx_cost_t;

affine_idx_cost_t affine_gap_1_over_3();
affine_idx_cost_t affine_gap_5_1();
sub_cost_t sub_cost_1();
sub_cost_t sub_cost_1_min_2();
sub_cost_t sub_cost_5_3_min_3();

#endif /* COST_H_ */
