/*
 * jaccard_similarity.h
 *
 *  Created on: 11 Dec 2012
 *      Author: johnathan
 */

#ifndef JACCARD_SIMILARITY_H_
#define JACCARD_SIMILARITY_H_

const float jaccard_similarity_custom(const char *str1, const char *str2, std_tokenizer_t *tokenizer);
const float jaccard_similarity(const char *str1, const char *str2);

#endif /* JACCARD_SIMILARITY_H_ */
