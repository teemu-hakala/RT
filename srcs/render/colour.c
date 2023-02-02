











#include "RT.h"

t_tuple	colour_at(t_world *world, t_ray ray)
{
	t_hit	hit;

	hit.hit_check = false;
	vec_clear(&world->intersections);
	intersect_world(world, ray);
	identify_hit(world, &hit);
	if (hit.hit_check == true)
	{
		prepare_object(world, &hit, ray);
		return (shade_hit(world, &hit));
	}
	else
		return (vector(0, 0, 0));
}
