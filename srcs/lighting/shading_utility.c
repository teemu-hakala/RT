#include "RT.h"

t_info	shade_plane(void *plane)
{
	t_info	temp;

	temp = get_lighting_info(((t_plane *)plane)->material, \
		((t_plane *)plane)->appearance, ((t_plane *)plane)->transform, \
			((t_plane *)plane)->material.init_colour);
	temp.f = planar_map;
	return (temp);
}

t_info	shade_sphere(void *sphere)
{
	t_info	temp;

	temp = get_lighting_info(((t_sphere *)sphere)->material, \
		((t_sphere *)sphere)->appearance, ((t_sphere *)sphere)->transform, \
			((t_sphere *)sphere)->material.init_colour);
	temp.f = spherical_map;
	return (temp);
}

t_info	shade_cone(void *cone)
{
	t_info	temp;

	temp = get_lighting_info(((t_cone *)cone)->material, \
		((t_cone *)cone)->appearance, ((t_cone *)cone)->transform, \
			((t_cone *)cone)->material.init_colour);
	temp.f = conical_map;
	return (temp);
}

t_info	shade_cylinder(void *cylinder)
{
	t_info	temp;

	temp = get_lighting_info(((t_cylinder *)cylinder)->material, \
		((t_cylinder *)cylinder)->appearance, \
			((t_cylinder *)cylinder)->transform, \
			((t_cylinder *)cylinder)->material.init_colour);
	temp.f = cylindrical_map;
	return (temp);
}

t_info	shade_cube(void *cube)
{
	t_info	temp;

	temp = get_lighting_info(((t_cube *)cube)->material, \
		((t_cube *)cube)->appearance, ((t_cube *)cube)->transform, \
			((t_cube *)cube)->material.init_colour);
	temp.f = cubic_map;
	return (temp);
}
