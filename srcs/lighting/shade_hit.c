#include "RT.h"

/* reflectance represents the fraction of light reflected*/

t_tuple	reflection_and_refraction(t_world *world, t_hit *hit)
{
	t_tuple		reflected;
	t_tuple		refracted;
	t_fl		reflectance;

	reflected = reflected_colour(world, hit);
	refracted = refracted_colour(world, hit);
	if (hit->intersection.material.reflectiveness > 0 && \
		hit->intersection.material.transparency > 0)
	{
		reflectance = schlick(hit);
		//printf("reflectance = %f\n", reflectance);
		return (tuple_add(tuple_scale(reflected, reflectance), \
			tuple_scale(refracted, (1 - reflectance))));
	}
	//printf("reflection: %0.2f, %0.2f, %0.2f\n", reflected.array[0], reflected.array[1], reflected.array[2]);
	//printf("refraction: %0.2f, %0.2f, %0.2f\n", refracted.array[0], refracted.array[1], refracted.array[2]);
	return (tuple_add(refracted, reflected));
}

t_tuple	shade_hit(t_world *world, t_hit *hit)
{
	t_tuple		colour;
	t_light		*light;
	uint64_t	i;
	t_tuple		reflected;

	colour = point(0, 0, 0);
	reflected = point(0, 0, 0);
	i = 0;
	while (i < world->lights.len)
	{
		light = (t_light *)vec_get(&world->lights, i);
		//is_shadow(world, hit->computations.over_point, light, hit);
		if (hit->intersection.appearance.pattern.type > 0 || \
		hit->intersection.appearance.texture.type > 0)
		{
			hit->intersection.material.init_colour = \
				get_appearance_colour(world, \
					&hit->computations.over_point, hit);
		}
		colour = tuple_add(colour, \
			lighting(world, light, hit->computations.vectors, \
				hit->computations.over_point, hit));
		i++;
	}
	if (hit->intersection.material.reflectiveness > 0 || hit->intersection.material.transparency > 0)
		reflected = reflection_and_refraction(world, hit);
	return (tuple_add(tuple_scale(colour, (1 - hit->intersection.material.reflectiveness)), reflected));
}
