/*
 * levenshtein.h
 *
 *  Created on: 20 Nov 2012
 *      Author: johnathan
 */

#ifndef LEVENSHTEIN_H_
#define LEVENSHTEIN_H_

unsigned int levenshtein(const char *s, const char *t);
float levenshtein_similarity(const char *str1, const char *str2);

#endif /* LEVENSHTEIN_H_ */
