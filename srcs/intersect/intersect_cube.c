#include "RT.h"

/* multiplying by infinity avoids dividing by zero,
	but ensures the sign remains correct*/

	/* cubes are composed of 6 planes */

t_fl	max_double(t_fl x, t_fl y, t_fl z)
{
	if (x >= y && x >= z)
		return (x);
	else if (y >= x && y >= z)
		return (y);
	else
		return (z);
}

static t_fl	min_double(t_fl x, t_fl y, t_fl z)
{
	if (x <= y && x <= z)
		return (x);
	else if (y <= x && y <= z)
		return (y);
	else
		return (z);
}

t_range	check_axis(t_fl origin, t_fl direction)
{
	t_range	numerator;
	t_range	result;
	double	temp;

	numerator.min = (-1 - origin);
	numerator.max = (1 - origin);
	if (fabs(direction) >= EPSILON)
	{
		result.min = numerator.min / direction;
		result.max = numerator.max / direction;
	}
	else
	{
		result.min = numerator.min * INFINITY;
		result.max = numerator.max * INFINITY;
	}
	if (result.min > result.max)
	{
		temp = result.min;
		result.min = result.max;
		result.max = temp;
	}
	return (result);
}

void	cube_intersection(t_ray ray, void *cube, t_world *world)
{
	t_intersect	temp;
	t_range		x;
	t_range		y;
	t_range		z;

	temp = set_intersect_info(((t_cube *)cube)->material, \
	((t_cube *)cube)->appearance,((t_cube *)cube)->transform, cubic_map);
	temp.shape = cube;
	ray = ray_transform(&ray, &((t_cube *)cube)->transform.inverse);
	x = check_axis(ray.origin.tuple.units.x, ray.direction.tuple.units.x);
	y = check_axis(ray.origin.tuple.units.y, ray.direction.tuple.units.y);
	z = check_axis(ray.origin.tuple.units.z, ray.direction.tuple.units.z);
	if (max_double(x.min, y.min, z.min) > min_double(x.max, y.max, z.max))
		return ;
	temp.time = max_double(x.min, y.min, z.min);
	if (vec_push(&world->intersections, &temp) == VEC_ERROR)
		handle_errors("vec_push malloc error cube_intersection");
	temp.time = min_double(x.max, y.max, z.max);
	if (vec_push(&world->intersections, &temp) == VEC_ERROR)
		handle_errors("vec_push malloc error cube_intersection");
}
