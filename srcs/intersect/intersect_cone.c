











#include "RT.h"

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
	params->discriminant = (params->b * params->b) - \
		(4 * params->a * params->c);
	params->res_1 = (-params->b - sqrt(params->discriminant)) / (2 * params->a);
	params->res_2 = (-params->b + sqrt(params->discriminant)) / (2 * params->a);
}

static void	intersect_cone_caps(t_object *cone, t_ray *ray, \
t_world *world)
{
	t_intersect	cap_intersect;

	cap_intersect.shape = *(t_object *)cone;
	if (cone->object.cone.closed == false || \
		(ray->direction.tuple.units.y < EPSILON && \
			ray->direction.tuple.units.y > -EPSILON))
		return ;
	cap_intersect.time = (cone->object.cone.min - \
		ray->origin.tuple.units.y) / ray->direction.tuple.units.y;
	if (check_cap(ray, cap_intersect.time, fabs(cone->object.cone.min)))
	{
		if (vec_push(&world->intersections, &cap_intersect) == VEC_ERROR)
			handle_errors("vec_push malloc error cyl_intersection");
	}
	cap_intersect.time = (cone->object.cone.max - \
		ray->origin.tuple.units.y) / ray->direction.tuple.units.y;
	if (check_cap(ray, cap_intersect.time, fabs(cone->object.cone.max)))
	{
		if (vec_push(&world->intersections, &cap_intersect) == VEC_ERROR)
			handle_errors("vec_push malloc error cone_intersection");
	}
}

void	cone_intersect_cont(t_quadratic params, t_ray ray, \
t_object *cone, t_world *world)
{
	t_fl		y0;
	t_intersect	temp;

	temp.shape = *(t_object *)cone;
	y0 = (ray.origin.tuple.units.y + double_min(params.res_1, params.res_2) \
		* ray.direction.tuple.units.y);
	if ((((t_object *)cone)->object.cone.min) < y0 && y0 < \
	(((t_object *)cone)->object.cone.max))
	{
		temp.time = double_min(params.res_1, params.res_2);
		if (vec_push(&world->intersections, &temp) == VEC_ERROR)
			handle_errors("vec_push malloc error cone_intersection");
	}
	y0 = ray.origin.tuple.units.y + double_max(params.res_1, params.res_2) \
	* ray.direction.tuple.units.y;
	if ((((t_object *)cone)->object.cone.min) < y0 && y0 < \
	(((t_object *)cone)->object.cone.max))
	{
		temp.time = double_max(params.res_1, params.res_2);
		if (vec_push(&world->intersections, &temp) == VEC_ERROR)
			handle_errors("vec_push malloc error cone_intersection");
	}
}

void	cone_intersection(t_ray ray, void *cone, t_world *world)
{
	t_quadratic	params;
	t_intersect	temp;

	ray = ray_transform(&ray, &((t_cone *)cone)->transform.inverse);
	cone_quadratic(&params, ray);
	if (params.a != 0 || params.b != 0)
	{
		if (params.a < EPSILON && params.a > -EPSILON)
		{
			temp.time = -params.c / (2 * params.b);
			temp.shape = *(t_object *)cone;
			if (vec_push(&world->intersections, &temp) == VEC_ERROR)
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
