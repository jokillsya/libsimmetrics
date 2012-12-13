/*
 * qgrams_distance.h
 *
 *  Created on: 11 Dec 2012
 *      Author: johnathan
 */

#ifndef QGRAMS_DISTANCE_H_
#define QGRAMS_DISTANCE_H_

const float qgrams_distance_custom(const char *str1, const char *str2, qgram_tokenizer_t *tokenizer);
const float qgrams_distance(const char *str1, const char *str2);
const float qgrams_distance_similarity_custom(const char *str1, const char *str2, qgram_tokenizer_t *tokenizer);
const float qgrams_distance_similarity(const char *str1, const char *str2);

#endif /* QGRAMS_DISTANCE_H_ */
