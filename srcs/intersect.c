/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:14:00 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/13 17:45:45 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/* circumference of sphere: 2πr.
Assume for now all spheres are unit spheres, therefore radius of 1 */

void	intersection(t_ray ray, t_objects shape, t_instance instance)
{



}

t_object sphere(t_tuple *origin, t_transform transform, t_tuple *colour)
{
	return ((t_object)
	{
		.object.sphere = (t_sphere)
		{
			.origin = (t_tuple){origin->tuple.x,
				origin->tuple.y,
				origin->tuple.z,
				origin->tuple.w},
			.transform = (t_transform){transform.translation,
				transform.rotation,
				transform.scale},
			.colour = (t_argb){origin->tuple.x,
				origin->tuple.y,
				origin->tuple.z,
				origin->tuple.w}
		},
		.type = OBJECT_SPHERE
	});
}

t_argb	hex_to_argb(uint32_t colour)
{
	return ((t_argb){.a = ((colour >> 24) & 0xFFu) / (t_fl)0xFFu,
		.r = ((colour >> 16) & 0xFFu) / (t_fl)0xFFu,
		.g = ((colour >> 8) & 0xFFu) / (t_fl)0xFFu,
		.b = (colour & 0xFFu) / (t_fl)0xFFu});
}

int main(void)
{
	t_ray		ray;
	t_objects	objects;
	t_argb		purple;

	purple = hex_to_argb(0x4c00b0);
	ray.origin.tuple = (t_units){ 0.0, 0.0, -5.0, 1.0 };
	ray.direction.tuple = (t_units){ 0.0, 0.0, 1.0, 0.0 };
}
