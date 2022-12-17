











#include "RT.h"
#include <stdio.h>
t_tuple	colour_at(t_world *world)
{
	vec_clear(&world->intersections);
	intersect_world(world, world->ray);
	identify_hit(world, &world->hit);
	if (world->hit.hit_check == true && world->ray.lifetime < 5) // && world->hit.intersection.time > 1)
		printf("time: %lf\n", world->hit.intersection.time);
	if (world->hit.hit_check == true)
	{
		prepare_computations(world);
		return (shade_hit(world));
	}
	else
		return (vector(0, 0, 0));
}
