/*
 * euclidean_distance.h
 *
 *  Created on: 10 Dec 2012
 *      Author: johnathan
 */

#ifndef EUCLIDEAN_DISTANCE_H_
#define EUCLIDEAN_DISTANCE_H_

const float euclidean_distance_custom(const char *str1, const char *str2, cost_t *cost);
const float euclidean_distance(const char *str1, const char *str2);
const float euclidean_distance_similarity_custom(const char *str1, const char *str2, cost_t * cost);
const float euclidean_distance_similarity(const char *str1, const char *str2);

#endif /* EUCLIDEAN_DISTANCE_H_ */
