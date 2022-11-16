/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_w.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:38:52 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/16 10:39:19 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

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
