/*
 * * Copyright (C) 2012 Johnathan Botha et al. All rights reserved.
 *
 * This file is part of libsimmetrics
 *
 * libsimmetrics is the C port of the Java project called Simmetrics,
 *
 * The Java code can be found here: https://github.com/Simmetrics/simmetrics
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * util.h
 *
 *  Created on: 20 Nov 2012
 *      Author: Johnathan Botha <jokillsya@gmail.com>
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
#ifdef _WIN32
//Custom implementation to make Mingw happy...
char * strtok_r(char *s, const char *delim, char **last);
#endif

#endif /* BIT_UTIL_H_ */
