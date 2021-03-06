/*
 * Copyright (C) 2014 Swift Navigation Inc.
 * Contact: Fergus Noble <fergus@swift-nav.com>
 *
 * This source is subject to the license found in the file 'LICENSE' which must
 * be be distributed together with this source. All other rights reserved.
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef LIBSWIFTNAV_MEMORY_POOL_H
#define LIBSWIFTNAV_MEMORY_POOL_H

#include <stddef.h>

#include "common.h"

/* Type for elements of the memory pool, unfortunately typedef doesn't enforce
 * type safety and an opaque struct definition wouldn't be compatible with the
 * flexible member array in node_t. */
typedef u8 element_t;

typedef struct _memory_pool memory_pool_t;

memory_pool_t *memory_pool_new(u32 n_elements, size_t element_size);
void memory_pool_destroy(memory_pool_t *pool);
s32 memory_pool_n_free(memory_pool_t *pool);
s32 memory_pool_n_allocated(memory_pool_t *pool);

element_t *memory_pool_add(memory_pool_t *pool);
s32 memory_pool_to_array(memory_pool_t *pool, void *array);

s32 memory_pool_map(memory_pool_t *pool, void (*f)(element_t *elem));
s32 memory_pool_filter(memory_pool_t *pool, s8 (*f)(element_t *elem));
s32 memory_pool_fold(memory_pool_t *pool, void *x0,
                     void (*f)(void *x, element_t *elem));
double memory_pool_dfold(memory_pool_t *pool, double x0,
                         double (*f)(double x, element_t *elem));
float memory_pool_ffold(memory_pool_t *pool, float x0,
                        float (*f)(float x, element_t *elem));
s32 memory_pool_ifold(memory_pool_t *pool, s32 x0,
                      s32 (*f)(s32 x, element_t *elem));

void memory_pool_sort(memory_pool_t *pool, void *arg,
                      s32 (*cmp)(void *arg, element_t *a, element_t *b));
void memory_pool_group_by(memory_pool_t *pool, void *arg,
                          s32 (*cmp)(void *arg, element_t *a, element_t *b),
                          void *x0, size_t x_size,
                          void (*agg)(element_t *new, void *x, u32 n, element_t *elem));
s32 memory_pool_product(memory_pool_t *pool, void *xs, u32 n_xs, size_t x_size,
                        void (*prod)(element_t *new, void *x, u32 n_xs, u32 n, element_t *elem));

#endif /* LIBSWIFTNAV_MEMORY_POOL_H */

