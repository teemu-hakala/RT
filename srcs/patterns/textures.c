
#include "RT.h"

void	no_texture_at(t_texture *texture, t_material *material, t_uv_map *map)
{
	(void)map;
	(void)texture;
	material->final_colour = material->init_colour;
}


void	checkered_at(t_texture *texture, t_material *material, t_uv_map *map)
{
	uint32_t u2;
	uint32_t v2;

	u2 = floor(map->u * texture->width);
	v2 = floor(map->v * texture->height);
	if ((u2 + v2) % 2 == 0)
		material->final_colour = texture->colour_a;
	else
		material->final_colour = texture->colour_b;
}

void	align_check_at(t_texture *texture, t_material *material, t_uv_map *map)
{
	material->final_colour = texture->main[texture->face];
	if (map->v > 0.8)
	{
		if (map->u < 0.2)
			material->final_colour = texture->ul[texture->face];
		if (map->u > 0.8)
			material->final_colour = texture->ur[texture->face];
	}
	else if (map->v < 0.2)
	{
		if (map->u < 0.2)
			material->final_colour = texture->bl[texture->face];
		if (map->u > 0.8)
			material->final_colour = texture->br[texture->face];
	}
	else
		material->final_colour = texture->main[texture->face];
}

void	external_at(t_texture *texture, t_material *material, t_uv_map *map)
{
	uint32_t u2;
	uint32_t v2;

	u2 = floor(map->u * texture->width);
	v2 = floor(map->v * texture->height);
	if ((u2 + v2) % 2 == 0)
		material->final_colour = texture->colour_a;
	else
		material->final_colour = texture->colour_b;
}
