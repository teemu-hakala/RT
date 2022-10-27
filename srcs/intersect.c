#include "RTv1.h"

/* circumference of sphere: 2πr.
Assume for now all spheres are unit spheres, therefore radius of 1

diameter of sphere: 2 * r
*/

void	identify_hit(t_world *world)
{
	t_intersect	*intersection;
	uint64_t	i;

	i = 0;

	world->hit.intersection = NULL;
	while (i < world->intersections.len)
	{
		intersection = \
			(t_intersect *)vec_get(&world->intersections, i++);

		if (intersection->time >= 0)
			if (world->hit.intersection == NULL \
				|| intersection->time < world->hit.intersection->time)
				world->hit.intersection = intersection;
	}
}


void	plane_intersection(t_ray ray, void *plane, t_world *world)
{
	(void)ray;
	(void)plane;
	(void)world;
}

void	sphere_intersection(t_ray ray, void *sphere, t_world *world)
{
	t_fl		discriminant;
	t_fl		a;
	t_fl		b;
	t_fl		c;
	t_tuple		sphere_to_ray;

	ray = ray_transform(&ray, &((t_sphere *)sphere)->transform.inverse);
	sphere_to_ray = tuple_sub(ray.origin, ((t_sphere *)sphere)->origin);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(ray.direction, sphere_to_ray);
	c = dot_product(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = (b * b) - 4 * a * c;
	if (discriminant >= 0.0)
	{
		if (vec_push(&world->intersections, &(t_intersect){
				.time = (-b - sqrt(discriminant)) / (2 * a),
				.shape = sphere
			}) == VEC_ERROR)
			handle_errors("vec_push malloc error sphere_intersection");
		if (vec_push(&world->intersections, &(t_intersect){
				.time = (-b + sqrt(discriminant)) / (2 * a),
				.shape = sphere
			}) == VEC_ERROR)
			handle_errors("vec_push malloc error sphere_intersection");
	}
}

void	cone_intersection(t_ray ray, void *cone, t_world *world)
{
	(void)ray;
	(void)cone;
	(void)world;
}

void	cylinder_intersection(t_ray ray, void *cylinder, t_world *world)
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
	uint64_t		i;

	i = (uint64_t)(-1);
	while (++i < world->objects.len)
	{
		intersect_object[((t_object *)vec_get(&world->objects, \
			i))->type - OBJECT_INDEX_OFFSET] \
			(world->ray, ((t_object *)vec_get(&world->objects, \
			i)), world);
	}
	vec_sort(&world->intersections, sort_intersections);
}