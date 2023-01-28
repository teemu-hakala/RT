#include "RT.h"

t_tuple	reflection_and_refraction(t_world *world)
{
	t_tuple		reflected;
	t_tuple		refracted;
	t_fl		reflectance;

	reflected = reflected_colour(world);
	refracted = refracted_colour(world);
	if (world->hit.intersection.material.reflectiveness > 0 && \
		world->hit.intersection.material.transparency > 0)
	{
		reflectance = schlick(world);
		return (tuple_add(tuple_scale(reflected, reflectance), \
			tuple_scale(refracted, (1 - reflectance))));
	}
	return (tuple_add(refracted, reflected));
}

t_tuple	shade_hit(t_world *world)
{
	t_tuple		colour;
	t_light		*light;
	uint64_t	i;

	colour = point(0, 0, 0);
	i = 0;
	while (i < world->lights.len)
	{
		light = (t_light *)vec_get(&world->lights, i);
		if (world->hit.intersection.appearance.pattern.type > 0 || \
		world->hit.intersection.appearance.texture.type > 0)
		{
			world->hit.intersection.material.init_colour = \
				get_appearance_colour(world, \
					&world->hit.computations.over_point);
		}
		colour = tuple_add(colour, \
			lighting(world, light, world->hit.computations.vectors, \
				world->hit.computations.over_point));
		i++;
	}
	return (tuple_add(colour, reflection_and_refraction(world)));
}
