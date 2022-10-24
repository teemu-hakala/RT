/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:27:10 by thakala           #+#    #+#             */
/*   Updated: 2022/10/16 12:13:12 by thakala          ###   ########.fr       */
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
	VEC_COPY_FULL = 2
};

int		vec_new(t_vec *src, uint64_t init_len, uint64_t elem_size);
void	vec_free(t_vec *src);
int		vec_from(t_vec *dst, void *src, uint64_t len, uint64_t elem_size);
int		vec_resize(t_vec *src, uint64_t target_len);
int		vec_clear(t_vec *src);
int		vec_push(t_vec *src, void *elem);
int		vec_pop(void *dst, t_vec *src);
int		vec_copy(t_vec *dst, t_vec *src);
void	*vec_get(t_vec *src, uint64_t index);
int		vec_insert(t_vec *dst, void *elem, uint64_t index);
int		vec_remove(t_vec *src, uint64_t index);
int		vec_append(t_vec *dst, t_vec *src);
int		vec_prepend(t_vec *dst, t_vec *src);
void	vec_iter(t_vec *src, void (*f) (void *));
void	*vec_find(t_vec *src, bool (*f) (void *));
int		vec_map(t_vec *dst, t_vec *src, void (*f) (void *));
int		vec_filter(t_vec *dst, t_vec *src, bool (*f) (void *));
int		vec_reduce(void *dst, t_vec *src, void (*f) (void *, void *));
int		vec_sort(t_vec *src, int (*f)(void *, void *));

#endif
