
#include "RT.h"

#include "RT.h"

void	shade_object(t_world *world, t_tuple *colour,
	t_light *light, t_info *light_info)
{
	t_tuple	surface_col;
	t_tuple	reflected_col;

	is_shadow(world, world->hit.computations.over_point, light);
	surface_col = lighting(light_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	if (light_info->appearance.pattern.type > 0 || \
		light_info->appearance.texture.type > 0)
	{
		light_info->col = get_appearance_colour(light_info, \
			&world->hit.computations.over_point, light_info->f);
		surface_col = lighting(light_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	}
	reflected_col = reflected_colour(world, &world->hit.computations);
	*colour = tuple_add(*colour, tuple_add(surface_col, reflected_col));
}
