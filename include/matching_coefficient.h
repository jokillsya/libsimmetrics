/*
 * matching_coefficient.h
 *
 *  Created on: 11 Dec 2012
 *      Author: johnathan
 */

#ifndef MATCHING_COEFFICIENT_H_
#define MATCHING_COEFFICIENT_H_

const float matching_coefficient_custom(const char *str1, const char *str2, std_tokenizer_t *tokenizer);
const float matching_coefficient(const char *str1, const char *str2);
const float matching_coefficient_similarity_custom(const char *str1, const char *str2, std_tokenizer_t *tokenizer);
const float matching_coefficient_similarity(const char *str1, const char *str2);

#endif /* MATCHING_COEFFICIENT_H_ */
