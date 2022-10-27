#include "RTv1.h"

t_tuple	colour_at(t_world *world)
{
	vec_clear(&world->intersections);
	intersect_world(world);
	identify_hit(world);
	if (world->hit.intersection != NULL)
	{
		prepare_computations(world);
		return (shade_hit(world));
	}
	else
		return (colour(0, 0, 0.5, 0.7));
}