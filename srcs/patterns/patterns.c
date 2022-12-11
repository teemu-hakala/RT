
#include "RT.h"

void	none_at(t_pattern *pattern, t_material *material, t_tuple *point)
{
	(void)point;
	(void)pattern;
	material->final_colour = material->init_colour;
}

void	striped_at(t_pattern *pattern, t_material *material, t_tuple *point)
{
	if (fmod(floor(point->tuple.units.x), 2) == 0)
		material->final_colour = pattern->colour_a;
	else
		material->final_colour = pattern->colour_b;
}

void	checkered_at(t_pattern *pattern, t_material *material, t_tuple *point)
{
	if (fmod((floor(point->tuple.units.x) + floor(point->tuple.units.y) + \
		floor(point->tuple.units.z)), 2) == 0)
		material->final_colour = pattern->colour_a;
	else
		material->final_colour = pattern->colour_b;
}

void	circle_at(t_pattern *pattern, t_material *material, t_tuple *point)
{
	t_fl	temp;

	temp = sqrt((point->tuple.units.x * point->tuple.units.x) + \
		(point->tuple.units.z * point->tuple.units.z));
	if (fmod(floor(temp), 2) == 0)
		material->final_colour = pattern->colour_a;
	else
		material->final_colour = pattern->colour_b;
}

void	gradient_at(t_pattern *pattern, t_material *material, t_tuple *point)
{
	t_fl	x_fraction;

	x_fraction = fabs(point->tuple.units.x) - floor(fabs(point->tuple.units.x));
	material->final_colour = tuple_add(pattern->colour_a, \
	tuple_scale(tuple_sub(pattern->colour_b, \
	pattern->colour_a), x_fraction));
}
