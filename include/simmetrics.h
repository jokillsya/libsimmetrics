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
 * simmetrics.h
 * 	Author: Johnathan Botha <jokillsya@gmail.com>
 *
 */

#ifndef libsimmetrics_H
#define libsimmetrics_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <libgen.h>
#include "utlist.h"
#include "utarray.h"
#include "uthash.h"
#include "tokenizer.h"
#include "qgrams_distance.h"
#include "block_distance.h"
#include "cosine_similarity.h"
#include "dice_similarity.h"
#include "euclidean_distance.h"
#include "jaccard_similarity.h"
#include "jaro.h"
#include "jaro_winkler.h"
#include "levenshtein.h"
#include "matching_coefficient.h"
#include "simmetrics.h"
#include "cost.h"
#include "monge_elkan.h"
#include "needleman_wunch.h"
#include "overlap_coefficient.h"
#include "smith_waterman.h"
#include "smith_waterman_gotoh.h"
#include "soundex.h"
#include "metaphone.h"
#include "double_metaphone.h"

typedef union {

	float (*custom_metric) (const char *, const char *, const void *);
	float (*metric) (const char *, const char *);

} metric_function_t;

typedef union {

	float (*custom_similarity) (const char *, const char *, const void *);
	float (*similarity) (const char *, const char *);

} similarity_function_t;

typedef union {

	int (*custom_distance) (const char *, const char *, const void *);
	int (*distance) (const char *, const char *);

} distance_function_t;

typedef union {

	char *(*normalize) (const char *);

} normalize_function_t;

distance_function_t* smc_block_distance();
similarity_function_t* smc_block_distance_similarity();
similarity_function_t* smc_cosine_similarity();
similarity_function_t* smc_dice_similarity();
metric_function_t* smc_euclidean_distance();
similarity_function_t* smc_euclidean_distance_similarity();
similarity_function_t* smc_jaccard_similarity();
similarity_function_t* smc_jaro_similarity();
similarity_function_t* smc_jaro_winkler_similarity();
distance_function_t* smc_levenshtein();
similarity_function_t* smc_levenshtein_similarity();
metric_function_t* smc_matching_coefficient();
similarity_function_t* smc_matching_coefficient_similarity();
normalize_function_t* smc_metaphone();
normalize_function_t* smc_double_metaphone();
similarity_function_t* smc_metaphone_similarity();
similarity_function_t* smc_double_metaphone_similarity();
similarity_function_t* smc_monge_elkan_similarity();
metric_function_t* smc_needleman_wunch();
similarity_function_t* smc_needleman_wunch_similarity();
similarity_function_t* smc_overlap_coefficient_similarity();
distance_function_t* smc_qgrams_distance();
similarity_function_t* smc_qgrams_distance_similarity();
metric_function_t* smc_smith_waterman();
similarity_function_t* smc_smith_waterman_similarity();
metric_function_t* smc_smith_waterman_gotoh();
similarity_function_t* smc_smith_waterman_gotoh_similarity();
normalize_function_t* smc_soundex();
similarity_function_t* smc_soundex_similarity();

#endif /* libsimmetrics_H */
