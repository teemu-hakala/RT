/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 10:20:50 by thakala           #+#    #+#             */
/*   Updated: 2022/10/23 10:42:29 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_object	sphere(t_tuple origin, t_transform transform, t_material material)
{
	return ((t_object)
		{
			.object.sphere = (t_sphere)
			{
				.origin = origin,
				.transform = transform,
				.material = material
			},
			.type = OBJECT_SPHERE
		}
	);
}
