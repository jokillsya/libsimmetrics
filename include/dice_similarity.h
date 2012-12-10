/*
 * dice_similarity.h
 *
 *  Created on: 10 Dec 2012
 *      Author: johnathan
 */

#ifndef DICE_SIMILARITY_H_
#define DICE_SIMILARITY_H_

const float dice_similarity_custom(const char *str1, const char *str2, cost_t *cost);
const float dice_similarity(const char *str1, const char *str2);

#endif /* DICE_SIMILARITY_H_ */
