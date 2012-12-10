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

} hash_token_t;

typedef struct ll_token_t {

	char *token;
	struct ll_token_t *next;

} ll_token_t;

typedef struct dl_token_t {

	char *token;
	struct dl_token_t *next, *prev;

} dl_token_t;

dl_token_t *tokenize_to_dllist(const char *str, const char *delimiters);
hash_token_t *merge_tokens(hash_token_t *t1, hash_token_t *t2);
hash_token_t *uq_tokenize_to_hash(const char *str, const char *delimiters);
UT_array *tokenize_to_utarray(const char *str, const char *delimiters);
void hash_token_free(hash_token_t *table);
void dll_token_free(dl_token_t *head);

#endif /* TOKENIZER_H_ */
