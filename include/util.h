/*
 * bit_util.h
 *
 *  Created on: 20 Nov 2012
 *      Author: johnathan
 */

#ifndef UTIL_H_
#define UTIL_H_

#define MIN(a, b) (((a < b)) ? (a) : (b))
#define MAX(a, b) (((a > b)) ? (a) : (b))
#define MIN3(a, b, c) (MIN(MIN(a, b), c))
#define MAX3(a, b, c) (MAX(MAX(a, b), c))
#define MIN4(a, b, c, d) (MIN(MIN3(a, b, c), d))
#define MAX4(a, b, c, d) (MAX(MAX3(a, b, c), d))

unsigned int str_hash(const char *s);

#endif /* BIT_UTIL_H_ */
