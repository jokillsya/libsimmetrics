/*
 * metaphone.h
 *
 *  Created on: Jan 18, 2013
 *      Author: bothajo
 */

#ifndef METAPHONE_H_
#define METAPHONE_H_

char *metaphone(const char *str);
float metaphone_similarity(const char *str1, const char *str2);

#endif /* METAPHONE_H_ */
