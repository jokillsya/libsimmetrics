/*
 * jaro_winkler.h
 *
 *  Created on: 20 Nov 2012
 *      Author: johnathan
 */

#ifndef JARO_WINKLER_H_
#define JARO_WINKLER_H_

#define MIN_PREF_LEN 6
#define PREF_ADJ_SCALE (float)0.1

float jaro_winkler_similarity(const char *str1, const char *str2);

#endif /* JARO_WINKLER_H_ */
