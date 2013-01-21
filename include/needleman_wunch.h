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
 * needleman_wunch.h
 *
 *  Created on: 26 Nov 2012
 *      Author: Johnathan Botha <jokillsya@gmail.com>
 */

#ifndef NEEDLEMAN_WUNCH_H_
#define NEEDLEMAN_WUNCH_H_

float needleman_wunch_custom(const char *str1, const char *str2, const void *v_conf);
float needleman_wunch(const char *str1, const char *str2);
float needleman_wunch_similarity_custom(const char *str1, const char *str2, const void *v_conf);
float needleman_wunch_similarity(const char *str1, const char *str2);

#endif /* NEEDLEMAN_WUNCH_H_ */
