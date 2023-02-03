/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_mapping_utility.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:39:31 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 11:39:33 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

int	face_from_point(t_tuple *p)
{
	t_fl	temp;

	temp = max_double(fabs(p->tuple.units.x), fabs(p->tuple.units.y), \
		fabs(p->tuple.units.z));
	if (temp == p->tuple.units.x)
		return (FACE_RIGHT);
	else if (temp == -p->tuple.units.x)
		return (FACE_LEFT);
	else if (temp == p->tuple.units.y)
		return (FACE_UP);
	else if (temp == -p->tuple.units.y)
		return (FACE_DOWN);
	else if (temp == p->tuple.units.z)
		return (FACE_FRONT);
	else
		return (FACE_BACK);
}

t_uv_map	cube_uv_right(t_tuple *p)
{
	t_uv_map	map;

	map.u = fmod((1 - p->tuple.units.z), 2) / 2;
	map.v = fmod((p->tuple.units.y + 1), 2) / 2;
	return (map);
}

t_uv_map	cube_uv_up(t_tuple *p)
{
	t_uv_map	map;

	map.u = fmod((p->tuple.units.x + 1), 2) / 2;
	map.v = fmod((1 - p->tuple.units.z), 2) / 2;
	return (map);
}

t_uv_map	cube_uv_down(t_tuple *p)
{
	t_uv_map	map;

	map.u = fmod((p->tuple.units.x + 1), 2) / 2;
	map.v = fmod((p->tuple.units.z + 1), 2) / 2;
	return (map);
}
