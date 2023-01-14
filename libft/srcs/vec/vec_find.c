/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:33:27 by thakala          #+#    #+#             */
/*   Updated: 2022/11/15 14:35:01 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec_find_result	vec_find(t_vec *haystack, \
	bool (*matcher)(void *, void *), void *needle, uint64_t from)
{
	uint64_t	u;
	void		*hay;

	u = from;
	while (u < haystack->len)
	{
		hay = vec_get(haystack, u);
		if (matcher(hay, needle))
			return ((t_vec_find_result){.result = hay, .at = u});
		u++;
	}
	return ((t_vec_find_result){.result = NULL, .at = -1});
}
