/*
 * tokenizer.h
 *
 *  Created on: 05 Dec 2012
 *      Author: johnathan
 */

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

typedef struct {

	unsigned int key;
	char *value;
	UT_hash_handle hh;

} tokenizer_t;

tokenizer_t *uq_tokenize_hash(const char *str, const char *delimiters);
void tokenizer_free(tokenizer_t *table);

#endif /* TOKENIZER_H_ */
