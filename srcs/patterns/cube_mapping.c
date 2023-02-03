/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:39:39 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 11:39:40 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

/*
	cube mapping:
							Up: +y
	Left: -x,	Front: +z,	Right: +x,	Back: -z
							Down: -y
*/

static t_uv_map	cube_uv_front(t_tuple *p)
{
	t_uv_map	map;

	map.u = fmod((p->tuple.units.x + 1), 2) / 2;
	map.v = fmod((p->tuple.units.y + 1), 2) / 2;
	return (map);
}

static t_uv_map	cube_uv_back(t_tuple *p)
{
	t_uv_map	map;

	map.u = fmod((1 - p->tuple.units.x), 2) / 2;
	map.v = fmod((p->tuple.units.y + 1), 2) / 2;
	return (map);
}

static t_uv_map	cube_uv_left(t_tuple *p)
{
	t_uv_map	map;

	map.u = fmod((p->tuple.units.z + 1), 2) / 2;
	map.v = fmod((p->tuple.units.y + 1), 2) / 2;
	return (map);
}

t_uv_map	cubic_map(t_tuple *p)
{
	t_fl		temp;

	temp = max_double(fabs(p->tuple.units.x), fabs(p->tuple.units.y), \
		fabs(p->tuple.units.z));
	if (temp == p->tuple.units.x)
		return (cube_uv_right(p));
	else if (temp == (p->tuple.units.x * -1))
		return (cube_uv_left(p));
	else if (temp == p->tuple.units.y)
		return (cube_uv_up(p));
	else if (temp == (p->tuple.units.y * -1))
		return (cube_uv_down(p));
	else if (temp == p->tuple.units.z)
		return (cube_uv_front(p));
	else
		return (cube_uv_back(p));
}
