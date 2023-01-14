/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:27:10 by thakala           #+#    #+#             */
/*   Updated: 2023/01/14 10:47:22 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>
# include "libft.h"

typedef struct s_vec
{
	uint8_t		*memory;
	uint64_t	elem_size;
	uint64_t	alloc_size;
	uint64_t	len;
}	t_vec;

enum e_vec_status
{
	VEC_ERROR = -1,
	VEC_NON_ACTION = 0,
	VEC_SUCCESS = 1,
	VEC_COPY_PARTIAL = 1,
	VEC_COPY_FULL = 2,
	VEC_BEGINNING = 0
};

typedef struct s_vec_find_result
{
	void		*result;
	uint64_t	at;
}	t_vec_find_result;

int			vec_new(t_vec *src, uint64_t init_len, uint64_t elem_size);
void		vec_free(t_vec *src);
int			vec_from(t_vec *dst, void *src, uint64_t len, uint64_t elem_size);
int			vec_resize(t_vec *src, uint64_t target_len);
int			vec_clear(t_vec *src);
int			vec_push(t_vec *dst, void *src);
int			vec_push_arr(t_vec *dst, void *src, uint64_t len);
int			vec_pop(void *dst, t_vec *src);
int			vec_copy(t_vec *dst, t_vec *src);
void		*vec_get(t_vec *src, uint64_t index);
int			vec_insert(t_vec *dst, void *elem, uint64_t index);
int			vec_remove(t_vec *src, uint64_t index);
int			vec_append(t_vec *dst, t_vec *src);
int			vec_prepend(t_vec *dst, t_vec *src);
void		vec_iter(t_vec *src, void (*f) (void *));
t_vec_find_result \
			vec_find(t_vec *haystack, \
				bool (*matcher)(void *, void *), void *needle, uint64_t from);
int			vec_map(t_vec *dst, t_vec *src, void (*f) (void *));
int			vec_filter(t_vec *dst, t_vec *src, bool (*f) (void *));
int			vec_reduce(void *dst, t_vec *src, void (*f) (void *, void *));
int			vec_sort(t_vec *src, int (*f)(void *, void *));
uint64_t	stick_size(uint64_t size);
uint64_t	check_addition_overflow(uint64_t a, uint64_t b);
uint64_t	check_multiplication_overflow(uint64_t multiplicand, \
			uint64_t multiplier);
void		vec_swap(t_vec *a, t_vec *b);
#endif
