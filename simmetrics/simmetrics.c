
#include "simmetrics.h"

distance_function_t* smc_block_distance() {

	distance_function_t *funcs = malloc(sizeof(distance_function_t));

	funcs->custom_distance = &block_distance_custom;
	funcs->distance = &block_distance;

	return (funcs);

}

similarity_function_t* smc_block_distance_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

//	funcs->custom_similarity = &block_distance_similarity_custom;
	funcs->similarity = &block_distance_similarity;

	return (funcs);

}

similarity_function_t* smc_cosine_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

	funcs->custom_similarity = &cosine_similarity_custom;
	funcs->similarity = &cosine_similarity;

	return (funcs);
}

similarity_function_t* smc_dice_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

	funcs->custom_similarity = &dice_similarity_custom;
	funcs->similarity = &dice_similarity;

	return (funcs);

}

metric_function_t* smc_euclidean_distance() {

	metric_function_t *funcs = (metric_function_t*) malloc(sizeof(metric_function_t));

	funcs->custom_metric = &euclidean_distance_custom;
	funcs->metric = &euclidean_distance;

	return (funcs);

}


similarity_function_t* smc_euclidean_distance_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

	funcs->custom_similarity = &euclidean_distance_similarity_custom;
	funcs->similarity = &euclidean_distance_similarity;

	return (funcs);

}

similarity_function_t* smc_jaccard_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

	funcs->custom_similarity = &jaccard_similarity_custom;
	funcs->similarity = &jaccard_similarity;

	return (funcs);

}

similarity_function_t* smc_jaro_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

//	funcs->custom_similarity = &jaro_similarity_custom;
	funcs->similarity = &jaro_similarity;

	return (funcs);

}

similarity_function_t* smc_jaro_winkler_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

//	funcs->custom_similarity = &jaro_winkler_similarity_custom;
	funcs->similarity = &jaro_winkler_similarity;

	return (funcs);

}

distance_function_t* smc_levenshtein() {

	distance_function_t *funcs = malloc(sizeof(distance_function_t));

//	funcs->custom_distance = &levenshtein_custom;
	funcs->distance = &levenshtein;

	return (funcs);

}

similarity_function_t* smc_levenshtein_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

//	funcs->custom_similarity = &levenshtein_similarity_custom;
	funcs->similarity = &levenshtein_similarity;

	return (funcs);

}

metric_function_t* smc_matching_coefficient() {

	metric_function_t *funcs = (metric_function_t*) malloc(sizeof(metric_function_t));

	funcs->custom_metric = &matching_coefficient_custom;
	funcs->metric = &matching_coefficient;

	return (funcs);

}

similarity_function_t* smc_matching_coefficient_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

	funcs->custom_similarity = &matching_coefficient_similarity_custom;
	funcs->similarity = &matching_coefficient_similarity;

	return (funcs);

}

normalize_function_t* smc_metaphone() {

	normalize_function_t *funcs = malloc(sizeof(normalize_function_t));

	funcs->normalize = &metaphone;

	return (funcs);

}

similarity_function_t* smc_metaphone_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

//	funcs->custom_similarity = &metaphone_similarity_custom;
	funcs->similarity = &metaphone_similarity;

	return (funcs);

}

normalize_function_t* smc_double_metaphone() {

	normalize_function_t *funcs = malloc(sizeof(normalize_function_t));

	funcs->normalize = &double_metaphone;

	return (funcs);

}

similarity_function_t* smc_double_metaphone_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

	funcs->similarity = &double_metaphone_similarity;

	return (funcs);

}

similarity_function_t* smc_monge_elkan_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

	funcs->custom_similarity = &monge_elkan_similarity_custom;
	funcs->similarity = &monge_elkan_similarity;

	return (funcs);

}

metric_function_t* smc_needleman_wunch() {

	metric_function_t *funcs = (metric_function_t*) malloc(sizeof(metric_function_t));

	funcs->custom_metric = &needleman_wunch_custom;
	funcs->metric = &needleman_wunch;

	return (funcs);

}

similarity_function_t* smc_needleman_wunch_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

	funcs->custom_similarity = &needleman_wunch_similarity_custom;
	funcs->similarity = &needleman_wunch_similarity;

	return (funcs);

}

similarity_function_t* smc_overlap_coefficient_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

	funcs->custom_similarity = &overlap_coefficient_similarity_custom;
	funcs->similarity = &overlap_coefficient_similarity;

	return (funcs);

}

distance_function_t* smc_qgrams_distance() {

	distance_function_t *funcs = malloc(sizeof(distance_function_t));

	funcs->custom_distance = &qgrams_distance_custom;
	funcs->distance = &qgrams_distance;

	return (funcs);

}

similarity_function_t* smc_qgrams_distance_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

	funcs->custom_similarity = &qgrams_distance_similarity_custom;
	funcs->similarity = &qgrams_distance_similarity;

	return (funcs);

}

metric_function_t* smc_smith_waterman() {

	metric_function_t *funcs = (metric_function_t*) malloc(sizeof(metric_function_t));

	funcs->custom_metric = &smith_waterman_custom;
	funcs->metric = &smith_waterman;

	return (funcs);

}

similarity_function_t* smc_smith_waterman_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

	funcs->custom_similarity = &smith_waterman_similarity_custom;
	funcs->similarity = &smith_waterman_similarity;

	return (funcs);

}

metric_function_t* smc_smith_waterman_gotoh() {

	metric_function_t *funcs = (metric_function_t*) malloc(sizeof(metric_function_t));

	funcs->custom_metric = &smith_waterman_gotoh_custom;
	funcs->metric = &smith_waterman_gotoh;

	return (funcs);

}

similarity_function_t* smc_smith_waterman_gotoh_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

	funcs->custom_similarity = &smith_waterman_gotoh_similarity_custom;
	funcs->similarity = &smith_waterman_gotoh_similarity;

	return (funcs);

}

normalize_function_t* smc_soundex() {

	normalize_function_t *funcs = malloc(sizeof(normalize_function_t));

	funcs->normalize = &soundex;

	return (funcs);

}

similarity_function_t* smc_soundex_similarity() {

	similarity_function_t *funcs = malloc(sizeof(similarity_function_t));

	funcs->similarity = &soundex_similarity;

	return (funcs);

}

