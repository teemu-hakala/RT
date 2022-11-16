/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:09:54 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/16 13:27:00 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	identify_hit(t_world *world, t_hit *hit)
{
	t_intersect	*intersection;
	uint64_t	i;

	i = 0;

	hit->hit_check = false;
	while (i < world->intersections.len)
	{
		intersection = \
			(t_intersect *)vec_get(&world->intersections, i++);
		if (intersection->time >= 0)
		{
			hit->intersection = *intersection;
			hit->hit_check = true;
			break ;
		}
	}
}

/*
void	identify_hit(t_world *world, t_hit *hit)
{
	t_intersect	*intersection;
	uint64_t	i;

	i = 0;

	hit->intersection = NULL;
	while (i < world->intersections.len)
	{
		intersection = \
			(t_intersect *)vec_get(&world->intersections, i++);
		if (intersection->time >= 0 && \
			(hit->intersection == NULL \
				|| intersection->time < hit->intersection->time))
		{
			hit->intersection = intersection;
			break ;
		}
	}
}
*/

void	plane_intersection(t_ray ray, void *plane, t_world *world)
{
	enum e_vec_status	result;

	ray = ray_transform(&ray, &((t_sphere *)plane)->transform.inverse);
	if (PLANE_EPSILON > ray.direction.tuple.units.y \
		&& ray.direction.tuple.units.y > -PLANE_EPSILON)
		return ;
	result = vec_push(&world->intersections, &(t_intersect){
			.time = -ray.origin.tuple.units.y / ray.direction.tuple.units.y,
			.shape = plane});
	if (result == VEC_ERROR)
		handle_errors("vec_push malloc error plane_intersection");
}

void	sphere_intersection(t_ray ray, void *sphere, t_world *world)
{
	t_quadratic	params;
	t_tuple		sphere_to_ray;

	ray = ray_transform(&ray, &((t_sphere *)sphere)->transform.inverse);
	sphere_to_ray = tuple_sub(ray.origin, ((t_sphere *)sphere)->origin);
	params.a = dot_product(ray.direction, ray.direction);
	params.b = 2 * dot_product(ray.direction, sphere_to_ray);
	params.c = dot_product(sphere_to_ray, sphere_to_ray) - 1;
	params.discriminant = (params.b * params.b) - 4 * params.a * params.c;
	if (params.discriminant >= 0.0)
	{
		if (vec_push(&world->intersections, &(t_intersect){
				.time = (-params.b - sqrt(params.discriminant)) / \
				(2 * params.a),
				.shape = sphere
			}) == VEC_ERROR)
			handle_errors("vec_push malloc error sphere_intersection");
		if (vec_push(&world->intersections, &(t_intersect){
				.time = (-params.b + sqrt(params.discriminant)) / \
				(2 * params.a),
				.shape = sphere
			}) == VEC_ERROR)
			handle_errors("vec_push malloc error sphere_intersection");
	}
}

t_fl	min(t_fl a, t_fl b)
{
	return (a < b ? a : b);
}

t_fl	max(t_fl a, t_fl b)
{
	return (a > b ? a : b);
}

void	cone_quadratic(t_quadratic *params, t_ray ray)
{
	params->a = (ray.direction.tuple.units.x * ray.direction.tuple.units.x) - \
		(ray.direction.tuple.units.y * ray.direction.tuple.units.y) \
		+ (ray.direction.tuple.units.z * ray.direction.tuple.units.z);
	params->b = (2 * ray.origin.tuple.units.x * ray.direction.tuple.units.x) - \
		(2 * ray.origin.tuple.units.y * ray.direction.tuple.units.y) + \
		(2 * ray.origin.tuple.units.z * ray.direction.tuple.units.z);
	params->c = (ray.origin.tuple.units.x * ray.origin.tuple.units.x) - \
		(ray.origin.tuple.units.y * ray.origin.tuple.units.y) + \
		(ray.origin.tuple.units.z * ray.origin.tuple.units.z);
	params->discriminant = (params->b * params->b) - (4 * params->a * params->c);
	params->res_1 = (-params->b - sqrt(params->discriminant)) / (2 * params->a);
	params->res_2 = (-params->b + sqrt(params->discriminant)) / (2 * params->a);
}

void	cone_intersect_cont(t_quadratic params, t_ray ray, \
t_object *cone, t_world *world)
{
	t_fl	y0;
	y0 = ray.origin.tuple.units.y + min(params.res_1, params.res_2) \
		* ray.direction.tuple.units.y;
	if ((((t_object *)cone)->object.cone.min) < y0 && y0 < \
	(((t_object *)cone)->object.cone.max))
	{
		if (vec_push(&world->intersections, &(t_intersect){
			.time = min(params.res_1, params.res_2),
			.shape = cone
			}) == VEC_ERROR)
		handle_errors("vec_push malloc error cone_intersection");
	}
	y0 = ray.origin.tuple.units.y + max(params.res_1, params.res_2) \
	* ray.direction.tuple.units.y;
	if ((((t_object *)cone)->object.cone.min) < y0 && y0 < \
	(((t_object *)cone)->object.cone.max))
	{
		if (vec_push(&world->intersections, &(t_intersect){
			.time = max(params.res_1, params.res_2),
			.shape = cone
			}) == VEC_ERROR)
		handle_errors("vec_push malloc error cone_intersection");
	}
}

void	cone_intersection(t_ray ray, void *cone, t_world *world)
{
	t_quadratic	params;

	ray = ray_transform(&ray, &((t_cone *)cone)->transform.inverse);
	cone_quadratic(&params, ray);
	if (params.a != 0 || params.b != 0)
	{
		if (params.a < EPSILON && params.a > -EPSILON)
		{
			if (vec_push(&world->intersections, &(t_intersect){
				.time = - params.c / (2 * params.b),
				.shape = cone
			}) == VEC_ERROR)
			handle_errors("vec_push malloc error cone_intersection");
		}
		else
		{
			if (params.discriminant >= 0.0)
				cone_intersect_cont(params, ray, cone, world);
		}
		intersect_cone_caps(cone, &ray, world);
	}
}

void	cylinder_quadratic(t_quadratic *params, t_ray ray)
{
	params->b = (2 * ray.origin.tuple.units.x * ray.direction.tuple.units.x) + \
	(2 * ray.origin.tuple.units.z * ray.direction.tuple.units.z);
	params->c = (ray.origin.tuple.units.x * ray.origin.tuple.units.x) + \
	(ray.origin.tuple.units.z * ray.origin.tuple.units.z) - 1;
	params->discriminant = (params->b * params->b) - (4 * params->a * params->c);
	params->res_1 = (-params->b - sqrt(params->discriminant)) / (2 * params->a);
	params->res_2 = (-params->b + sqrt(params->discriminant)) / (2 * params->a);
}

void	cylinder_intersection_cont(t_quadratic params, t_ray ray, \
t_object *cylinder, t_world *world)
{
	t_fl y0;

	y0 = ray.origin.tuple.units.y + min(params.res_1, params.res_2) \
	* ray.direction.tuple.units.y;
	if (cylinder->object.cylinder.min < y0 && y0 < cylinder->object.cylinder.max)
	{
		if (vec_push(&world->intersections, &(t_intersect){
			.time = min(params.res_1, params.res_2),
			.shape = cylinder
		}) == VEC_ERROR)
		handle_errors("vec_push malloc error cylinder_intersection");
	}
	y0 = ray.origin.tuple.units.y + max(params.res_1, params.res_2) \
	* ray.direction.tuple.units.y;
	if (cylinder->object.cylinder.min < y0 && y0 < cylinder->object.cylinder.max)
	{
		if (vec_push(&world->intersections, &(t_intersect){
				.time = max(params.res_1, params.res_2),
				.shape = cylinder
			}) == VEC_ERROR)
			handle_errors("vec_push malloc error cylinder_intersection");
	}
}

void	cylinder_intersection(t_ray ray, void *cylinder, t_world *world)
{
	t_quadratic	params;

	ray = ray_transform(&ray, &((t_cylinder *)cylinder)->transform.inverse);
	params.a = (ray.direction.tuple.units.x * ray.direction.tuple.units.x) + \
		(ray.direction.tuple.units.z * ray.direction.tuple.units.z);
	if (params.a > EPSILON || params.a < -EPSILON)
	{
		cylinder_quadratic(&params, ray);
		if (params.discriminant >= 0.0)
			cylinder_intersection_cont(params, ray, cylinder, world);
	}
	intersect_cylinder_caps(cylinder, &ray, world);
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

void	intersect_world(t_world *world, t_ray ray)
{
	static const t_intersect_function	\
					intersect_object[] = \
	{
		plane_intersection,
		sphere_intersection,
		cone_intersection,
		cylinder_intersection
	};
	uint64_t		i;

	i = (uint64_t)(-1);
	while (++i < world->objects.len)
	{
		intersect_object[((t_object *)vec_get(&world->objects, \
			i))->type - OBJECT_INDEX_OFFSET] \
			(ray, ((t_object *)vec_get(&world->objects, \
			i)), world);
	}
	vec_sort(&world->intersections, sort_intersections);
}
