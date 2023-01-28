











#include "RT.h"

/*this function checks whether the intersection is within the cylinder's
radius*/

int	check_cap(t_ray *ray, t_fl time, t_fl radius)
{
	t_fl	x;
	t_fl	z;

	x = ray->origin.tuple.units.x + time * ray->direction.tuple.units.x;
	z = ray->origin.tuple.units.z + time * ray->direction.tuple.units.z;
	if ((x * x) + (z * z) <= radius)
		return (true);
	else
		return (false);
}

/* checks to see whether the ray intersects the end caps of the
cylinder and if true adds the intersection to the world intersect list */

static void	intersect_cylinder_caps(t_object *cylinder, t_ray *ray, \
t_world *world)
{
	t_intersect	cap_intersect;

	cap_intersect = set_intersect_info(((t_cylinder *)cylinder)->material, \
	((t_cylinder *)cylinder)->appearance, ((t_cylinder *)cylinder)->transform, \
		cylindrical_map);
	cap_intersect.shape = cylinder;
	if (cylinder->object.cylinder.closed == false || \
		(ray->direction.tuple.units.y < EPSILON && \
		ray->direction.tuple.units.y > -EPSILON))
		return ;
	cap_intersect.time = (cylinder->object.cylinder.min - \
		ray->origin.tuple.units.y) / ray->direction.tuple.units.y;
	if (check_cap(ray, cap_intersect.time, cylinder->object.cylinder.radius))
	{
		if (vec_push(&world->intersections, &cap_intersect) == VEC_ERROR)
			handle_errors("vec_push malloc error cyl_intersection");
	}
	cap_intersect.time = (cylinder->object.cylinder.max - \
		ray->origin.tuple.units.y) / ray->direction.tuple.units.y;
	if (check_cap(ray, cap_intersect.time, cylinder->object.cylinder.radius))
	{
		if (vec_push(&world->intersections, &cap_intersect) == VEC_ERROR)
			handle_errors("vec_push malloc error cylinder_intersection");
	}
}

static void	cylinder_quadratic(t_quadratic *params, t_ray ray)
{
	params->b = (2 * ray.origin.tuple.units.x * ray.direction.tuple.units.x) + \
		(2 * ray.origin.tuple.units.z * ray.direction.tuple.units.z);
	params->c = (ray.origin.tuple.units.x * ray.origin.tuple.units.x) + \
		(ray.origin.tuple.units.z * ray.origin.tuple.units.z) - 1;
	params->discriminant = (params->b * params->b) - \
		(4 * params->a * params->c);
	params->res_1 = (-params->b - sqrt(params->discriminant)) / (2 * params->a);
	params->res_2 = (-params->b + sqrt(params->discriminant)) / (2 * params->a);
}

static void	cylinder_intersection_cont(t_quadratic params, t_ray ray, \
t_object *cylinder, t_world *world)
{
	t_fl		y0;
	t_intersect	temp;

	temp = set_intersect_info(((t_cylinder *)cylinder)->material, \
	((t_cylinder *)cylinder)->appearance, ((t_cylinder *)cylinder)->transform, \
		cylindrical_map);
	temp.shape = cylinder;
	y0 = ray.origin.tuple.units.y + double_min(params.res_1, params.res_2) \
		* ray.direction.tuple.units.y;
	if (cylinder->object.cylinder.min < y0 && \
		y0 < cylinder->object.cylinder.max)
	{
		temp.time = double_min(params.res_1, params.res_2);
		if (vec_push(&world->intersections, &temp) == VEC_ERROR)
			handle_errors("vec_push malloc error cylinder_intersection");
	}
	y0 = ray.origin.tuple.units.y + double_max(params.res_1, params.res_2) \
		* ray.direction.tuple.units.y;
	if (cylinder->object.cylinder.min < y0 && \
		y0 < cylinder->object.cylinder.max)
	{
		temp.time = double_max(params.res_1, params.res_2);
		if (vec_push(&world->intersections, &temp) == VEC_ERROR)
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
