#include "RTv1.h"

t_tuple	colour_at(t_world *world)
{
	t_tuple		result_colour;

	vec_clear(&world->intersections);
	intersect_world(world);
	identify_hit(world);
	prepare_computations(world);
	if (world->hit.intersection->time >= 0)
	{
		return (shade_hit(world));
	}
	else
		return (colour(0, 0, 0, 0));
}