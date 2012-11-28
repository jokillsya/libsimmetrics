/*
 * needleman_wunch.h
 *
 *  Created on: 26 Nov 2012
 *      Author: johnathan
 */

#ifndef NEEDLEMAN_WUNCH_H_
#define NEEDLEMAN_WUNCH_H_

float custom_needleman_wunch(const char *str1, const char *str2, sub_cost_t *conf);
float needleman_wunch(const char *str1, const char *str2);
float custom_needleman_wunch_similarity(const char *str1, const char *str2, sub_cost_t *conf);
float needleman_wunch_similarity(const char *str1, const char *str2);

#endif /* NEEDLEMAN_WUNCH_H_ */
