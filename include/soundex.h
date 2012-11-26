/*
 * soundex.h
 *
 *  Created on: 20 Nov 2012
 *      Author: johnathan
 */

#ifndef SOUNDEX_H_
#define SOUNDEX_H_

/**
 * Returned char* must be manually freed
 */
char *soundex(const char *_str);
float soundex_similarity(const char *str1, const char *str2);

#endif /* SOUNDEX_H_ */
