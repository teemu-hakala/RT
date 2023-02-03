/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_w.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:34:22 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 11:34:24 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_tuple	point(t_fl x, t_fl y, t_fl z)
{
	return ((t_tuple){
		.tuple.units.x = x,
		.tuple.units.y = y,
		.tuple.units.z = z,
		.tuple.units.w = POINT_1
	});
}

t_tuple	vector(t_fl x, t_fl y, t_fl z)
{
	return ((t_tuple){
		.tuple.units.x = x,
		.tuple.units.y = y,
		.tuple.units.z = z,
		.tuple.units.w = VECTOR_0
	});
}
