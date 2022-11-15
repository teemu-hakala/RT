/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_prepend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:40:46 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 14:40:55 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int vec_prepend(t_vec *dst, t_vec *src)
{
	if (vec_append(src, dst) > VEC_NON_ACTION)
		vec_swap(dst, src);
	return ((-(dst->memory == NULL)) | 0x1);
}
