/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:14:00 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/25 15:24:26 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/* circumference of sphere: 2πr.
Assume for now all spheres are unit spheres, therefore radius of 1

diameter of sphere: 2 * r
*/

void	prepare_computations(t_world *world, t_ray *ray)
{

}

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

void	plane_intersection(t_ray *ray, t_object *plane, t_vec *intersections)
{
	(void)ray;
	(void)plane;
	(void)intersections;
}

void	sphere_intersection(t_ray *ray, t_object *shape, t_vec *intersections)
{
	t_fl	discriminant;
	t_fl	a;
	t_fl	b;
	t_fl	c;
	t_tuple	sphere_to_ray;
	t_intersect	intersect;

	*ray = ray_transform(ray, &shape->object.sphere.transform.inverse);
	sphere_to_ray = tuple_sub(ray->origin, shape->object.sphere.origin);
	a = dot_product(ray->direction, ray->direction);
	b = 2.0f * dot_product(ray->direction, sphere_to_ray);
	c = dot_product(sphere_to_ray, sphere_to_ray) - 1.0f;
	discriminant = (b * b) - 4.0f * a * c;
	if (discriminant < 0.0)
	{
		return ; // do we want to record somewhere that the intersection number for this shape == 0?
	}
	else
	{
		intersect.time = (-b - sqrt(discriminant)) / (2.0f * a);
		intersect.shape = shape;
		vec_push(intersections, &intersect);
		if (discriminant <= 1)
		{
			intersect.time = (-b + sqrt(discriminant)) / (2.0f * a);
			vec_push(intersections, &intersect);
		}
		else
		{
			intersect.time += (2.0f * shape->object.sphere.transform.scale.tuple.units.x); //radius * 2;
			vec_push(intersections, &intersect);
		}
	}
}

void	cone_intersection(t_ray *ray, t_object *cone, t_vec *intersections)
{
	(void)ray;
	(void)cone;
	(void)intersections;
}

void	cylinder_intersection(t_ray *ray, t_object *cylinder, t_vec *intersections)
{
	(void)ray;
	(void)cylinder;
	(void)intersections;
}

int sort_intersections(void *xs_a, void *xs_b)
{
	t_intersect *a;
	t_intersect *b;
	t_fl diff;

	a = (t_intersect *)xs_a;
	b = (t_intersect *)xs_b;
	diff = a->time - b->time;
	if (diff > 0)
		return (1);
	else if (diff == 0)
		return (0);
	else
		return (-1);

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