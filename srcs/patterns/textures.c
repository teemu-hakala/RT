
#include "RT.h"

void	none_at(t_pattern *pattern, t_material *material, t_uv_map *map)
{
	(void)map;
	(void)pattern;
	material->final_colour = material->init_colour;
}

void	vertical_striped_at(t_pattern *pattern, t_material *material, \
	t_uv_map *map)
{
	if (fmod(floor(point->tuple.units.x), 2) == 0)
		material->final_colour = pattern->colour_a;
	else
		material->final_colour = pattern->colour_b;
	(void)map;
	(void)pattern;
	material->final_colour = material->init_colour;
}

void	horizontal_striped_at(t_pattern *pattern, t_material *material, \
	t_uv_map *map)
{
	// if (fmod(floor(point->tuple.units.y), 2) == 0)
	// 	material->final_colour = pattern->colour_a;
	// else
	// 	material->final_colour = pattern->colour_b;
	(void)map;
	(void)pattern;
	material->final_colour = material->init_colour;
}

void	checkered_at(t_pattern *pattern, t_material *material, t_uv_map *map)
{
	uint32_t u2;
	uint32_t v2;

	u2 = floor(map->u * pattern->width);
	v2 = floor(map->v * pattern->height);
	if ((u2 + v2) % 2 == 0)
		material->final_colour = pattern->colour_a;
	else
		material->final_colour = pattern->colour_b;
	// if (fmod((floor(point->tuple.units.x) + floor(point->tuple.units.y) + \
	// 	floor(point->tuple.units.z)), 2) == 0)
	// 	material->final_colour = pattern->colour_a;
	// else
	// 	material->final_colour = pattern->colour_b;
}

void	circle_at(t_pattern *pattern, t_material *material, t_uv_map *map)
{
	// t_fl	temp;

	// temp = sqrt((point->tuple.units.x * point->tuple.units.x) + \
	// 	(point->tuple.units.z * point->tuple.units.z));
	// if (fmod(floor(temp), 2) == 0)
	// 	material->final_colour = pattern->colour_a;
	// else
	// 	material->final_colour = pattern->colour_b;
	(void)map;
	(void)pattern;
	material->final_colour = material->init_colour;
}

void	gradient_at(t_pattern *pattern, t_material *material, t_uv_map *map)
{
	// t_fl	x_fraction;

	// x_fraction = fabs(point->tuple.units.x) - floor(fabs(point->tuple.units.x));
	// material->final_colour = tuple_add(pattern->colour_a, \
	// tuple_scale(tuple_sub(pattern->colour_b, \
	// pattern->colour_a), x_fraction));
	(void)map;
	(void)pattern;
	material->final_colour = material->init_colour;
}

void	align_check_at(t_pattern *pattern, t_material *material, t_uv_map *map)
{
	material->final_colour = pattern->main[pattern->face];
	if (map->v > 0.8)
	{
		if (map->u < 0.2)
			material->final_colour = pattern->ul[pattern->face];
		if (map->u > 0.8)
			material->final_colour = pattern->ur[pattern->face];
	}
	else if (map->v < 0.2)
	{
		if (map->u < 0.2)
			material->final_colour = pattern->bl[pattern->face];
		if (map->u > 0.8)
			material->final_colour = pattern->br[pattern->face];
	}
	else
		material->final_colour = pattern->main[pattern->face];
}
