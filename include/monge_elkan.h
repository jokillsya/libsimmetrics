/*
 * monge_elkan.h
 *
 *  Created on: 26 Nov 2012
 *      Author: johnathan
 */

#ifndef MONGE_ELKAN_H_
#define MONGE_ELKAN_H_

float custom_monge_elkan_similarity(const char *str1, const char *str2, metric_function_t *metric, const void *v_conf, const cost_type_e cost_type);
float monge_elkan_similarity(const char *str1, const char *str2);

#endif /* MONGE_ELKAN_H_ */
