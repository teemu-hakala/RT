
#include "RT.h"

void	no_texture_at(t_texture *texture, t_uv_map *map, t_tuple *colour)
{
	(void)map;
	(void)texture;
	(void)colour;
}


void	checkered_at(t_texture *texture, t_uv_map *map, t_tuple *colour)
{
	uint32_t	u2;
	uint32_t	v2;

	u2 = floor(map->u * texture->width);
	v2 = floor(map->v * texture->height);
	if ((u2 + v2) % 2 == 0)
		*colour = texture->colour_a;
	else
		*colour = texture->colour_b;
}

void	align_check_at(t_texture *texture, t_uv_map *map, t_tuple *colour)
{
	*colour = texture->main[texture->face];
	if (map->v > 0.8)
	{
		if (map->u < 0.2)
			*colour = texture->ul[texture->face];
		if (map->u > 0.8)
			*colour = texture->ur[texture->face];
	}
	else if (map->v < 0.2)
	{
		if (map->u < 0.2)
			*colour = texture->bl[texture->face];
		if (map->u > 0.8)
			*colour = texture->br[texture->face];
	}
	else
		*colour = texture->main[texture->face];
}

void	external_at(t_texture *texture, t_uv_map *map, t_tuple *colour)
{
	t_fl	x;
	t_fl	y;

	map->v = 1 - map->v;
	x = map->u * (texture->image[texture->face].width - 1);
	y = map->v * (texture->image[texture->face].height - 1);
	*colour = \
		texture->image[texture->face].pixels[(int)y][(int)x];
}

/* this is a pattern - but here because of the 5 functions per rule page*/

void	simple_checkered_at(t_pattern *pattern, t_tuple *point, t_tuple *colour)
{
	if (fmod((floor(point->tuple.units.x) + floor(point->tuple.units.y) + \
		floor(point->tuple.units.z)), 2) == 0)
		*colour = pattern->colour_a;
	else
		*colour = pattern->colour_b;
}
