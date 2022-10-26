/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:14:00 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/26 10:12:32 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/* circumference of sphere: 2πr.
Assume for now all spheres are unit spheres, therefore radius of 1

diameter of sphere: 2 * r
*/

/*void	prepare_computations(t_vec *intersections, t_ray *ray)
{
	h
}*/

// void	identify_hit(t_intersections *array)
// {
// 	int	i;
// 	int	hit;

// 	i = -1;
// 	hit = -1;
// 	while (++i < array->num)
// 	{
// 		if (array->intersections[i].time >= 0 && hit == -1)
// 		{
// 			hit = i;
// 			array->intersections[i].hit = 1;
// 		}
// 		else
// 			array->intersections[i].hit = 0;
// 	}
// }

void	identify_hit(t_world *world, uint64_t index, uint64_t num)
{
	t_intersect	*intersection;
	uint64_t	hit_index;
	uint64_t	i;

	hit_index = (uint64_t)(-1);
	i = 0;
	while (i < num)
	{
		intersection = (t_intersect *)vec_get(&world->intersections, \
			(index - num + i));
		if (intersection->time >= 0 && hit_index == (uint64_t)(-1))
			hit_index = i;
		i++;
	}
	if (hit_index != (uint64_t)(-1))
		if (vec_push(&world->hits, vec_get(&world->intersections, \
			index - num + hit_index)) == (uint64_t)(-1))
			handle_errors("vec_push malloc error sphere_intersection");
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
	uint64_t	index;

	ray = ray_transform(&ray, &shape->object.sphere.transform.inverse);
	sphere_to_ray = tuple_sub(ray.origin, shape->object.sphere.origin);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(ray.direction, sphere_to_ray);
	c = dot_product(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = (b * b) - 4 * a * c;
	if (discriminant >= 0.0)
	{
		index = vec_push(&world->intersections, &(t_intersect){
			.time = (-b - sqrt(discriminant)) / (2 * a),
			.shape = shape
		});
		if (index == (uint64_t)(-1))
			handle_errors("vec_push malloc error sphere_intersection");
		index = vec_push(&world->intersections, &(t_intersect){
			.time = (-b + sqrt(discriminant)) / (2 * a),
			.shape = shape
		});
		if (index == (uint64_t)(-1))
			handle_errors("vec_push malloc error sphere_intersection");
		identify_hit(world, index + 1, 2);
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

void	intersect_world(t_world *world)
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

	world->ray = (t_ray){.origin = point(0, 0, -5), .direction = vector(0, 0, 1)};
	i = -1;
	while (++i < world->objects.len)
	{
		intersect_object[((t_object *)vec_get(&world->objects, i))->type] \
			(world->ray, ((t_object *)vec_get(&world->objects, i)), \
			world);
	}
	vec_sort(&world->intersections, sort_intersections);
}