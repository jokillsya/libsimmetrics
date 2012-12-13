/*
 * cosine_similarity.h
 *
 *  Created on: 10 Dec 2012
 *      Author: johnathan
 */

#ifndef COSINE_SIMILARITY_H_
#define COSINE_SIMILARITY_H_

const float cosine_similarity_custom(const char *str1, const char *str2, std_tokenizer_t *tokenizer);
const float cosine_similarity(const char *str1, const char *str2);

#endif /* COSINE_SIMILARITY_H_ */
