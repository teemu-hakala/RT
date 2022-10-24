/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:28:30 by thakala           #+#    #+#             */
/*   Updated: 2022/10/16 16:17:12 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_new(t_vec *dst, uint64_t init_len, uint64_t elem_size)
{
	dst->len = 0;
	dst->elem_size = elem_size;
	dst->alloc_size = init_len;
	if (dst->alloc_size > 0 && elem_size > 0)
		dst->memory = (uint8_t *)malloc(dst->elem_size * dst->alloc_size);
	else
		dst->memory = NULL;
	return ((-(!dst->memory && ((!init_len && !elem_size) || !elem_size))) \
		| !!elem_size);
}

void	vec_free(t_vec *src)
{
	free(src->memory);
	ft_bzero(src, sizeof(t_vec));
}

int	vec_from(t_vec *dst, void *src, uint64_t len, uint64_t elem_size)
{
	if (vec_new(dst, len, elem_size) > 0)
	{
		ft_memcpy(dst->memory, src, len * elem_size);
		dst->len = len;
	}
	return ((-(dst->memory == NULL)) | 0x1);
}

int	vec_copy(t_vec *dst, t_vec *src)
{
	if (src->len > dst->alloc_size)
	{
		ft_memcpy(dst->memory, src->memory, src->elem_size * dst->alloc_size);
		dst->len = dst->alloc_size;
		return (VEC_COPY_PARTIAL);
	}
	else
	{
		ft_memcpy(dst->memory, src->memory, src->elem_size * src->len);
		dst->len = src->len;
		return (VEC_COPY_FULL);
	}
}

/*static*/
int	vec_resize(t_vec *src, uint64_t	target_size)
{
	t_vec	data;

	data = *src;
	if (vec_new(src, target_size, src->elem_size) > 0)
	{
		vec_copy(src, &data);
		free(data.memory);
	}
	return (src->memory != NULL);
}

int	vec_push(t_vec *dst, void *src)
{
	if (dst->alloc_size <= dst->len)
		if (vec_resize(dst, dst->alloc_size * 2) <= 0)
			return (VEC_ERROR);
	ft_memcpy(&dst->memory[dst->len * dst->elem_size], src, dst->elem_size);
	dst->len++;
	return (VEC_SUCCESS);
}

int	vec_pop(void *dst, t_vec *src)
{
	if (src->len >= 1ULL)
	{
		ft_memcpy(dst,
			&src->memory[--src->len * src->elem_size],
			src->elem_size);
		return (VEC_SUCCESS);
	}
	return (VEC_ERROR);
}

void	*vec_get(t_vec *src, uint64_t index)
{
	return (&src->memory[index * src->elem_size]);
}

int	vec_insert(t_vec *dst, void *src, uint64_t index)
{
	if (dst->alloc_size >= dst->len + 1)
	{
		ft_memmove(&dst->memory[dst->elem_size * (index + 1)],
			&dst->memory[dst->elem_size * index],
			dst->elem_size * (dst->len - index));
		dst->len++;
		ft_memcpy(&dst->memory[dst->elem_size * index], src, dst->elem_size);
	}
	else
	{
		if (vec_resize(dst, dst->alloc_size * 2) > VEC_NON_ACTION)
			return (vec_insert(dst, src, index));
		return (VEC_ERROR);
	}
	return (VEC_SUCCESS);
}

int	vec_remove(t_vec *src, uint64_t index)
{
	ft_memmove(&src->memory[src->elem_size * index],
		&src->memory[src->elem_size * (index + 1)],
		src->elem_size * (src->len - index - 1));
	src->len--;
	return (VEC_SUCCESS);
}

int	vec_append(t_vec *dst, t_vec *src)
{
	uint64_t	dst_prev_len;

	if (dst->alloc_size - dst->len < src->len)
	{
		dst_prev_len = dst->len;
		if (vec_resize(dst, dst->len + src->len) > 0)
		{
			ft_memcpy(&dst->memory[dst->elem_size * dst_prev_len],
				src->memory,
				dst->elem_size * src->len);
			dst->len += src->len;
		}
	}
	else
	{
		ft_memcpy(&dst->memory[dst->len],
			&src->memory,
			dst->elem_size * src->len);
		dst->len += src->len;
	}
	return ((-(dst->memory == NULL)) | 0x1);
}

static void	vec_swap(t_vec *a, t_vec *b)
{
	t_vec	swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

int vec_prepend(t_vec *dst, t_vec *src)
{
	if (vec_append(src, dst) > VEC_NON_ACTION)
		vec_swap(dst, src);
	return ((-(dst->memory == NULL)) | 0x1);
}

void	vec_iter(t_vec *src, void (*f) (void *))
{
	uint64_t	c;

	c = 0;
	while (c < src->len)
		f(vec_get(src, c++));
}

int	vec_map(t_vec *dst, t_vec *src, void (*f) (void *))
{
	uint64_t	c;

	vec_copy(dst, src);
	c = -1;
	while (++c < src->len)
		f(&dst->memory[dst->elem_size * c]);
	return (VEC_SUCCESS);
}

int	vec_filter(t_vec *dst, t_vec *src, bool (*f)(void *))
{
	uint64_t	c;
	void		*data;

	c = -1;
	while (++c < src->len)
	{
		data = &src->memory[src->elem_size * c];
		if (f(data))
			if (vec_push(dst, data) < VEC_NON_ACTION)
				return (VEC_ERROR);
	}
	return (VEC_SUCCESS);
}

int	vec_reduce(void *acc, t_vec *src, void (*f)(void *, void *))
{
	uint64_t	c;

	c = -1;
	while (++c < src->len)
		f(acc, &src->memory[src->elem_size * c]);
	return (VEC_SUCCESS);
}

static int	vec_swap_elems(uint64_t elem_size, void *a, void *b)
{
	uint8_t		*swap;

	swap = (uint8_t *)malloc(sizeof(uint8_t) * elem_size);
	if (swap == NULL)
		return (VEC_ERROR);
	ft_memcpy(swap, a, elem_size);
	ft_memcpy(a, b, elem_size);
	ft_memcpy(b, swap, elem_size);
	free(swap);
	return (VEC_SUCCESS);
}

int	vec_sort(t_vec *src, int (*f)(void *, void *))
{
	uint64_t	c;

	c = -1;
	while (++c < src->len - 1)
	{
		if (f(&src->memory[src->elem_size * c],
				&src->memory[src->elem_size * (c + 1)]) > 0)
		{
			if (vec_swap_elems(src->elem_size,
					&src->memory[src->elem_size * c],
					&src->memory[src->elem_size * (c + 1)]) < VEC_NON_ACTION)
				return (VEC_ERROR);
			c = -1;
		}
	}
	return (VEC_SUCCESS);
}
