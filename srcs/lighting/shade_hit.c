#include "RT.h"


t_tuple	shade_hit(t_world *world, t_hit *hit)
{
	t_tuple		colour;
	t_light		*light;
	uint64_t	i;
	t_tuple		reflection;

	colour = point(0, 0, 0);
	i = 0;
	while (i < world->lights.len)
	{
		light = (t_light *)vec_get(&world->lights, i);
		is_shadow(world, hit, light);
		if (hit->intersection.appearance.pattern.type > 0 || \
		hit->intersection.appearance.texture.type > 0)
		{
			hit->intersection.material.init_colour = \
				get_appearance_colour(hit, &hit->computations.over_point);
		}
		colour = tuple_add(colour, \
			lighting(light, hit->computations.vectors, hit));
		i++;
	}
	reflection = reflected_colour(world, hit);
	return (tuple_add(colour, reflection));
}
