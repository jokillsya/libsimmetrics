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

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "dyn_array.h"

static void d_arr_shift(d_array_t *pool);
static int d_arr_new_size(d_array_t *pool, size_t datsize, size_t *size);
static int d_arr_resize(d_array_t *pool, size_t datsize);

static void d_arr_shift(d_array_t *pool) {
	if (pool->v_buf != pool->v_basebuf) {
		memmove(pool->v_basebuf, pool->v_buf, pool->v_off);
		pool->v_buf = pool->v_basebuf;
	}
}

static int d_arr_new_size(d_array_t *pool, size_t datsize, size_t *size) {
	size_t need;
	size_t rem;

	if (datsize <= pool->v_size - pool->v_off) {
		*size = pool->v_size;
		return (0);
	}

	/* Check limit of new requested size */
	if (pool->v_limit - pool->v_off < datsize)
		return (EFBIG);
	need = pool->v_off + datsize;

	/* Check limit of new size aligned to block size */
	rem = need % pool->v_blksize;
	if (rem != 0) {
		if (pool->v_limit - pool->v_off >= datsize + (pool->v_blksize - rem))
			need += pool->v_blksize - rem;
		else
			need = pool->v_limit;
	}

	*size = need;
	return (0);
}

static int d_arr_resize(d_array_t *pool, size_t datsize) {
	char *ret;
	size_t size;
	int error;

	error = d_arr_new_size(pool, datsize, &size);
	if (error != 0)
		return (error);

	if (size > pool->v_size) {
		ret = (char *) malloc(size);
		if (ret == NULL )
			return (ENOMEM);

		memcpy(ret, pool->v_buf, pool->v_off);
		free(pool->v_basebuf);
		pool->v_basebuf = pool->v_buf = ret;
		pool->v_size = size;
	} else if ((pool->v_size - pool->v_off) - (pool->v_buf - pool->v_basebuf)
			< datsize)
		d_arr_shift(pool);

	return (0);
}

void d_arr_init(d_array_t *pool, size_t blksize, size_t limit) {

	pool->v_basebuf = pool->v_buf = NULL;
	pool->v_off = pool->v_size = 0;

	pool->v_blksize = (blksize == 0) ? 4096 : blksize; /* XXX */
	pool->v_limit = (limit == 0) ? SIZE_MAX : limit;

	pool->v_lasterr = 0;
}

void d_arr_free(d_array_t *pool) {
	free(pool->v_basebuf);
}

void d_arr_reset(d_array_t *pool) {
	free(pool->v_basebuf);
	pool->v_basebuf = pool->v_buf = NULL;
	pool->v_off = pool->v_size = 0;
	pool->v_lasterr = 0;
}

void d_arr_wipe(d_array_t *pool) {
	pool->v_off = 0;
	pool->v_lasterr = 0;
}

void *
d_arr_ins(d_array_t *pool, size_t where, void *data, size_t datsize) {
	char *ret;
	int error;

	error = d_arr_resize(pool, datsize);
	if (error != 0) {
		pool->v_lasterr = error;
		return (NULL );
	}

	/*
	 * If ``where'' is greater than or equal to offset then
	 * we are appending data to the end of the buffer.
	 */
	if (where > pool->v_off)
		where = pool->v_off;

	ret = (char *) pool->v_buf + where;
	if (pool->v_off - where > 0)
		memmove(ret + datsize, ret, pool->v_off - where);
	memcpy(ret, data, datsize);
	pool->v_off += datsize;
	pool->v_lasterr = 0;

	return (ret);
}

void *
d_arr_exp(d_array_t *pool, size_t where, size_t size) {
	char *ret;
	int error;

	error = d_arr_resize(pool, size);
	if (error != 0) {
		pool->v_lasterr = error;
		return (NULL );
	}

	/*
	 * If ``where'' is greater than or equal to offset then
	 * we are appending data to the end of the buffer.
	 */
	if (where > pool->v_off)
		where = pool->v_off;

	ret = (char *) pool->v_buf + where;
	if (pool->v_off - where > 0)
		memmove(ret + size, ret, pool->v_off - where);
	pool->v_off += size;
	pool->v_lasterr = 0;

	return (ret);
}

int d_arr_trunc(d_array_t *pool, size_t where, size_t size, d_arr_trunc_e how) {
	/* Check if caller wants to remove more data than we have */
	if (where >= pool->v_off || size > pool->v_off
			|| pool->v_off - size < where) {
		pool->v_lasterr = ERANGE;
		return (pool->v_lasterr);
	}

	if (how == DARR_EXCLUDE) {
		if (where == 0) {
			/*
			 * Optimization.
			 * Don't move data, just adjust pointer.
			 */
			pool->v_buf = ((char *)pool->v_buf) + size;
			//((char *) pool->v_buf) += size;
		} else {
			memmove((char *) pool->v_buf + where,
					(char *) pool->v_buf + where + size,
					pool->v_off - size - where);
		}
		pool->v_off -= size;
	} else {
		pool->v_buf += where;
		pool->v_off = size;
	}

	pool->v_lasterr = 0;
	return (0);
}

void d_arr_export(d_array_t *pool, void **buf, size_t *size) {
	d_arr_shift(pool);
	*buf = pool->v_buf;
	*size = pool->v_off;
	pool->v_basebuf = pool->v_buf = NULL;
	pool->v_off = pool->v_size = 0;
	pool->v_lasterr = 0;
}
