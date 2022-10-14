/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:14:00 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/14 14:15:56 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/* circumference of sphere: 2πr.
Assume for now all spheres are unit spheres, therefore radius of 1

diameter of sphere: 2 * r
*/

void	sphere_intersection(t_ray *ray, t_object *shape, t_intersections *array)
{
	t_fl discriminant;
	t_fl a;
	t_fl b;
	t_fl c;
	t_tuple sphere_to_ray;

	sphere_to_ray = tuple_sub(&ray->origin, &shape->object.sphere.origin);
	a = dot_product(&ray->direction, &ray->direction);
	b = 2 * dot_product(&ray->direction, &sphere_to_ray);
	c = dot_product(&sphere_to_ray, &sphere_to_ray) - 1;

	discriminant = (b * b) - 4 * a * c;
	printf("discriminant = %f\n", discriminant);
	if (discriminant < 0.0)
	{
		array->num = 0;
		return ;
	}
	else
	{
		array->num = 2; // for other shapes can do num = (uint64)discriminant;
		array->intersections = (t_intersect *)malloc(sizeof(t_intersect) * 2);
		if (!array->intersections)
			handle_errors("intersect malloc fail");
		if (discriminant <= 1)
		{
			array->intersections[0].time = (-b - sqrt(discriminant)) / (2 * a);
			array->intersections[0].shape = shape;
			array->intersections[1].time = (-b + sqrt(discriminant)) / (2 * a);
			array->intersections[1].shape = shape;
		}
		else
		{
			array->intersections[0].time = (-b - sqrt(discriminant)) / (2 * a);
			array->intersections[0].shape = shape;
			array->intersections[1].time = array->intersections[0].time + 2;
			array->intersections[1].shape = shape;
		}
	}
}

t_object sphere(t_tuple *origin, t_transform *transform, t_tuple *colour)
{
	return ((t_object)
	{
		.object.sphere = (t_sphere)
		{
			.origin = (t_tuple){.tuple.units = (t_units)
				{origin->tuple.units.x,
				origin->tuple.units.y,
				origin->tuple.units.z,
				origin->tuple.units.w}},
			.transform = (t_transform){transform->translation,
				transform->rotation,
				transform->scale},
			.colour = (t_tuple){.tuple.colour = (t_colour)
				{colour->tuple.colour.a,
				colour->tuple.colour.r,
				colour->tuple.colour.g,
				colour->tuple.colour.b}}
		},
		.type = OBJECT_SPHERE
	});
}

t_tuple	hex_to_argb(uint32_t colour)
{
	return ((t_tuple){.tuple.colour.a = ((colour >> 24) & 0xFFu) / (t_fl)0xFFu,
		.tuple.colour.r = ((colour >> 16) & 0xFFu) / (t_fl)0xFFu,
		.tuple.colour.g = ((colour >> 8) & 0xFFu) / (t_fl)0xFFu,
		.tuple.colour.b = (colour & 0xFFu) / (t_fl)0xFFu});
}

// int main(void)
// {
// 	t_ray		ray;
// 	t_objects	objects;
// 	t_tuple		purple;
// 	t_transform transform;
// 	t_object	object_sphere;

// 	purple = hex_to_argb(0x4c00b0);
// 	ray.origin.tuple.units = (t_units){ 0.0, 0.0, -5.0, 1.0 };
// 	ray.direction.tuple.units = (t_units){ 0.0, 0.0, 1.0, 0.0 };
// 	transform =(t_transform)
// 	{
// 		.translation = (t_tuple)
// 		{
// 			.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1 }
// 		},
// 		.rotation = (t_tuple)
// 		{
// 			.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1 }
// 		},
// 		.scale = (t_tuple)
// 		{
// 			.tuple.units = (t_units){ 1.0, 1.0, 1.0, POINT_1 }
// 		}
// 	};
// 	objects.list = (t_object *)malloc(sizeof(t_object) * 3);
// 	if (objects.list == NULL)
// 		exit(EXIT_FAILURE);
// 	object_sphere = sphere(
// 			&(t_tuple){.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1}},
// 			&transform,
// 			&purple
// 		);
// }
