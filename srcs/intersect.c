/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:14:00 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/25 10:49:27 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/* circumference of sphere: 2πr.
Assume for now all spheres are unit spheres, therefore radius of 1

diameter of sphere: 2 * r
*/

void	identify_hit(t_intersections *array)
{
	int	i;
	int	hit;

	i = -1;
	hit = -1;
	while (++i < array->num)
	{
		if (array->intersections[i].time >= 0 && hit == -1)
		{
			hit = i;
			array->intersections[i].hit = 1;
		}
		else
			array->intersections[i].hit = 0;
	}
}

void	plane_intersection(t_ray *ray, t_object *plane, t_intersections *array)
{
	(void)ray;
	(void)plane;
	(void)array;
}

// void	sphere_intersection(t_ray *ray, t_object *shape, t_intersections *array)
// {
// 	t_fl	discriminant;
// 	t_fl	a;
// 	t_fl	b;
// 	t_fl	c;
// 	t_tuple	sphere_to_ray;

// 	sphere_to_ray = tuple_sub(ray->origin, shape->object.sphere.origin);
// 	a = dot_product(ray->direction, ray->direction);
// 	b = 2 * dot_product(ray->direction, sphere_to_ray);
// 	c = dot_product(sphere_to_ray, sphere_to_ray) - 1;
// 	discriminant = (b * b) - 4 * a * c;
// 	if (discriminant < 0.0)
// 	{
// 		array->num = 0;
// 		array->intersections = NULL;
// 		return ;
// 	}
// 	else
// 	{
// 		array->num = 2;
// 		array->intersections = (t_intersect *)malloc(sizeof(t_intersect) * 2);
// 		if (!array->intersections)
// 			handle_errors("sphere_intersection array->intersections malloc fail");
// 		if (discriminant <= 1)
// 		{
// 			array->intersections[0].time = (-b - sqrt(discriminant)) / (2 * a);
// 			array->intersections[0].shape = shape;
// 			array->intersections[1].time = (-b + sqrt(discriminant)) / (2 * a);
// 			array->intersections[1].shape = shape;
// 		}
// 		else
// 		{
// 			array->intersections[0].time = (-b - sqrt(discriminant)) / (2 * a);
// 			array->intersections[0].shape = shape;
// 			array->intersections[1].time = array->intersections[0].time + 2; // radius * 2
// 			array->intersections[1].shape = shape;
// 		}
// 	}
// 	identify_hit(array);
// }

void	sphere_intersection(t_ray *ray, t_object *shape, t_world *world)
{
	t_fl	discriminant;
	t_fl	a;
	t_fl	b;
	t_fl	c;
	t_tuple	sphere_to_ray;
	t_intersect	intersect;

	sphere_to_ray = tuple_sub(ray->origin, shape->object.sphere.origin);
	a = dot_product(ray->direction, ray->direction);
	b = 2 * dot_product(ray->direction, sphere_to_ray);
	c = dot_product(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = (b * b) - 4 * a * c;
	if (discriminant < 0.0)
	{
		return ;
	}
	else
	{
		intersect.time = (-b - sqrt(discriminant)) / (2 * a);
		intersect.shape = shape;
		vec_push(&world->intersections, &intersect);
		if (discriminant <= 1)
		{
			intersect.time = (-b + sqrt(discriminant)) / (2 * a);
			vec_push(&world->intersections, &intersect);
		}
		else
		{
			intersect.time += 2; //radius * 2;
			vec_push(&world->intersections, &intersect);
		}
	}
	// identify_hit(array);
}

void	cone_intersection(t_ray *ray, t_object *cone, t_intersections *array)
{
	(void)ray;
	(void)cone;
	(void)array;
}

void	cylinder_intersection(t_ray *ray, t_object *cylinder, t_intersections *array)
{
	(void)ray;
	(void)cylinder;
	(void)array;
}

void sort_intersections(void *xs_a, void *xs_b)
{
	t_intersect *a;
	t_intersect *b;

	a = (t_intersect *)xs_a;
	b = (t_intersect *)xs_b;
	return (a->time - b->time);

}

void	intersect_world(t_world *world, t_ray ray)
{
	uint64_t i;
	static const t_intersect_function	\
					intersect_object[] = \
	{
		plane_intersection,
		sphere_intersection,
		cone_intersection,
		cylinder_intersection
	};

	i = -1;
	while (++i < world->objects.len)
	{
		intersect_object[((t_object *)vec_get(&world->objects, i))->type] \
			(&ray, ((t_object *)vec_get(&world->objects, i)), \
			&world->intersections);
	}
	vec_sort(&world->intersections, sort_intersections);
}