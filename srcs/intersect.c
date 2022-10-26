/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:14:00 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/26 13:32:20 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/* circumference of sphere: 2πr.
Assume for now all spheres are unit spheres, therefore radius of 1

diameter of sphere: 2 * r
*/

void	prepare_computations(t_intersect *intersection, t_world *world)
{
	t_comp temp;

	temp.time = intersection->time;
	temp.point = hit_position(&world->ray, temp.time);
	temp.eyev = tuple_scale(world->ray.direction, -1);
	temp.normalv = normal_at_sphere(object, &temp.point);
}

void	identify_hit(t_world *world, uint64_t index, uint64_t num)
{
	t_intersect	*intersection;
	t_intersect	*closest;
	uint64_t	hit_index;
	uint64_t	i;

	closest = NULL;
	i = 0;
	while (i < num)
	{
		intersection = (t_intersect *)vec_get(&world->intersections, \
			(index - num + i));
		if (intersection->time >= 0 && closest == NULL)
			closest = intersection;
		i++;
	}
	if (closest != NULL)
		if (vec_push(&world->hits, closest) == VEC_ERROR)
			handle_errors("vec_push malloc error sphere_intersection");
	prepare_computations(vec_get(&world->hits, world->hits.len - 1), world);
}

void	plane_intersection(t_ray ray, t_object *plane, t_world *world)
{
	(void)ray;
	(void)plane;
	(void)world;
}

void	sphere_intersection(t_ray ray, t_object *shape, t_world *world)
{
	t_fl		discriminant;
	t_fl		a;
	t_fl		b;
	t_fl		c;
	t_tuple		sphere_to_ray;

	ray = ray_transform(&ray, &shape->object.sphere.transform.inverse);
	sphere_to_ray = tuple_sub(ray.origin, shape->object.sphere.origin);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(ray.direction, sphere_to_ray);
	c = dot_product(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = (b * b) - 4 * a * c;
	if (discriminant >= 0.0)
	{
		if (vec_push(&world->intersections, &(t_intersect){
				.time = (-b - sqrt(discriminant)) / (2 * a),
				.shape = shape
			}) == VEC_ERROR)
			handle_errors("vec_push malloc error sphere_intersection");
		if (vec_push(&world->intersections, &(t_intersect){
				.time = (-b + sqrt(discriminant)) / (2 * a),
				.shape = shape
			}) == VEC_ERROR)
			handle_errors("vec_push malloc error sphere_intersection");
		identify_hit(world, world->intersections.len, 2);
	}
}

void	cone_intersection(t_ray ray, t_object *cone, t_world *world)
{
	(void)ray;
	(void)cone;
	(void)world;
}

void	cylinder_intersection(t_ray ray, t_object *cylinder, t_world *world)
{
	(void)ray;
	(void)cylinder;
	(void)world;
}

int sort_intersections(void *xs_a, void *xs_b)
{
	t_intersect	*a;
	t_intersect	*b;
	t_fl		diff;

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

void	intersect_world(t_world *world)
{
	static const t_intersect_function	\
					intersect_object[] = \
	{
		plane_intersection,
		sphere_intersection,
		cone_intersection,
		cylinder_intersection
	};

	world->ray = (t_ray){.origin = point(0, 0, -5), \
		.direction = vector(0, 0, 1)};
	world->object_index = (uint64_t)(-1);
	while (++world->object_index < world->objects.len)
	{
		intersect_object[((t_object *)vec_get(&world->objects, \
			world->object_index))->type] \
			(world->ray, ((t_object *)vec_get(&world->objects, \
			world->object_index)), world);
	}
	vec_sort(&world->intersections, sort_intersections);
}