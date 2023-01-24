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
	t_info	light_info;

	colour.tuple.colour = (t_colour){0.0, 0.0, 0.0, 0.0};
	i = 0;
	while (i < world->lights.len)
	{
		light = (t_light *)vec_get(&world->lights, i);
		light_info = shape_shading[world->hit.intersection.shape->type] \
			(&world->hit.intersection.shape->object);
		shade_object(world, &colour, light, &light_info);
		i++;
	}
	return (colour);
}
