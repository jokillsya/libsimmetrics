/*
 * block_distance.h
 *
 *  Created on: 05 Dec 2012
 *      Author: johnathan
 */

#ifndef BLOCK_DISTANCE_H_
#define BLOCK_DISTANCE_H_

int block_distance_custom(const char * str1, const char *str2, std_tokenizer_t *tokenizer);
int block_distance(const char * str1, const char *str2);
float block_distance_similarity_custom(const char *str1, const char *str2, std_tokenizer_t *tokenizer);
float block_distance_similarity(const char *str1, const char *str2);

#endif /* BLOCK_DISTANCE_H_ */
