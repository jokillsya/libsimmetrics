/*
 * dyn_array.h
 *
 *  Created on: Nov 19, 2012
 *      Author: bothajo
 */

#ifndef DYN_ARRAY_H_
#define DYN_ARRAY_H_

/*
 * Copyright (c) 2006, 2008 Alexey Vatchenko <av@bsdua.org>
 *
 * (Modified by Johnathan Botha (c) 2012)
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/types.h>

#include <limits.h>

/**
 * JB - Compat for C99 on MINGW - window$
 */
#ifndef	SIZE_MAX
#define	SIZE_MAX	ULONG_MAX	/* max value for a size_t */
#endif

typedef struct d_array_t {

	void *v_basebuf; /* pointer returned by (re|m)alloc() */
	void *v_buf; /* actual data starts here */

	size_t v_off;
	size_t v_size;

	size_t v_blksize;
	size_t v_limit;

	int v_lasterr;

} d_array_t;

typedef enum d_arr_trunc_e {
	DARR_EXCLUDE, DARR_INCLUDE
} d_arr_trunc_e;

#define DARR_TAIL	UINT_MAX

void d_arr_init(d_array_t *pool, size_t blksize, size_t limit);
void d_arr_free(d_array_t *pool);

void d_arr_reset(d_array_t *pool);
void d_arr_wipe(d_array_t *pool);

void * d_arr_ins(d_array_t *pool, size_t where, void *data, size_t datsize);
void * d_arr_exp(d_array_t *pool, size_t where, size_t size);

int d_arr_trunc(d_array_t *pool, size_t where, size_t size, d_arr_trunc_e how);

#define d_arr_is_empty(pool)		((pool)->v_off == 0)
#define d_arr_get_buf(pool)		((pool)->v_buf)
#define d_arr_get_length(pool)		((pool)->v_off)
#define d_arr_get_error(pool)		((pool)->v_lasterr)

void d_arr_export(d_array_t *pool, void **buf, size_t *size);

#endif /* DYN_ARRAY_H_ */
