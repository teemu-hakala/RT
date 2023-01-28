#include "RT.h"

t_tuple	shade_hit(t_world *world)
{
	static const t_shading_function	\
				shape_shading[] = {
		shade_plane,
		shade_sphere,
		shade_cone,
		shade_cylinder,
		shade_cube
	};
	t_tuple		colour;
	t_light		*light;
	uint64_t	i;
	t_info		light_info;
	t_tuple		reflected;
	t_tuple		refracted;
	t_fl		reflectance;

	colour = point(0, 0, 0);
	i = 0;
	while (i < world->lights.len)
	{
		light = (t_light *)vec_get(&world->lights, i);
		light_info = shape_shading[world->hit.intersection.shape->type] \
			(&world->hit.intersection.shape->object);
		if (light_info.appearance.pattern.type > 0 || \
		light_info.appearance.texture.type > 0)
	{
		light_info.col = get_appearance_colour(light_info, \
			&world->hit.computations.over_point, light_info.f);
	}
		colour = tuple_add(colour, \
			lighting(&light_info, light, world->hit.computations.vectors, \
				world->hit.computations.over_point));
		i++;
	}
	reflected = reflected_colour(world, &world->hit.computations);
	refracted = refracted_colour(world, &world->hit.computations);
	if (light_info.material.reflectiveness > 0 && light_info.material.transparency > 0)
	{
		reflectance = schlick(world->hit.computations);
		return (tuple_add(colour, tuple_add(tuple_scale(reflected, reflectance),\
			tuple_scale(refracted, (1- reflectance)))));
	}
	return (tuple_add(refracted, tuple_add(colour, reflected)));
}
