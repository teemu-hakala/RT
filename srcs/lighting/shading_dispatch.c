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

	colour.tuple.colour = (t_colour){0.0, 0.0, 0.0, 0.0};
	i = 0;
	while (i < world->lights.len)
	{
		light = (t_light *)vec_get(&world->lights, i);
		shape_shading[world->hit.intersection.shape->type] \
			(world, &world->hit.intersection.shape->object, &colour, light);
		i++;
	}
	return (colour);
}
