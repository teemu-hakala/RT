
#include "RT.h"

void	none_at(t_pattern *pattern, t_material *material, t_tuple *point)
{
	(void)point;
	(void)pattern;
	material->final_colour = material->init_colour;
}

void	vertical_striped_at(t_pattern *pattern, t_material *material, \
	t_tuple *point)
{
	if (fmod(floor(point->tuple.units.x), 2) == 0)
		material->final_colour = pattern->colour_a;
	else
		material->final_colour = pattern->colour_b;

}

void	horizontal_striped_at(t_pattern *pattern, t_material *material, \
	t_tuple *point)
{
	if (fmod(floor(point->tuple.units.y), 2) == 0)
		material->final_colour = pattern->colour_a;
	else
		material->final_colour = pattern->colour_b;
}

void	circle_at(t_pattern *pattern, t_material *material, t_tuple *point)
{
	if (fmod(floor(sqrt((point->tuple.units.x * point->tuple.units.x) + \
	(point->tuple.units.z * point->tuple.units.z))), 2) == 0)
		material->final_colour = pattern->colour_a;
	else
		material->final_colour = pattern->colour_b;
}

void	gradient_at(t_pattern *pattern, t_material *material, t_tuple *point)
{
	t_fl	x_fraction;

	x_fraction = fabs(point->tuple.units.x) - floor(fabs(point->tuple.units.x));
	if (x_fraction < 0.5)
		material->final_colour = tuple_add(pattern->colour_a, \
		tuple_scale(tuple_sub(pattern->colour_b, \
		pattern->colour_a), x_fraction));
	else
		material->final_colour = tuple_add(pattern->colour_b, \
		tuple_scale(tuple_sub(pattern->colour_a, \
		pattern->colour_b), x_fraction));
}
