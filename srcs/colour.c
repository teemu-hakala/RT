











#include "RT.h"

t_tuple	colour_at(t_world *world, t_ray ray)
{
	vec_clear(&world->intersections);
	intersect_world(world, ray);
	identify_hit(world, &world->hit);
	if (0 && world->lifetime == 0)
		printf("lifetime over\n");
	if (world->hit.hit_check == true)
	{
		prepare_computations(world, ray);
		return (shade_hit(world));
	}
	else
		return (vector(0, 0, 0));
}
