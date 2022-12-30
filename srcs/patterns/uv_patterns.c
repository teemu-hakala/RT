#include "RT.h"

typedef struct s_uv_pattern
{
	t_fl	width;
	t_fl	height;
	t_tuple	colour_a;
	t_tuple	colour_b;
}				t_uv_pattern;

typedef struct s_uv_map
{
	t_fl	u;
	t_fl	v;
}			t_uv_map;

typedef struct s_texture_map
{
	t_uv_pattern pattern;
	t_uv_map	map;
}				t_texture_map;


t_uv_pattern uv_checkers(t_fl width, t_fl height, t_tuple col_a, t_tuple col_b)
{
	return ((t_uv_pattern){
			.width = width,
			.height = height,
			.colour_a = col_a,
			.colour_b = col_b
	});
}

t_uv_map	spherical_map(t_tuple p)
{
	t_fl		theta;
	t_tuple		vec;
	t_fl		radius;
	t_fl		phi;
	t_fl		raw_u;
	t_uv_map	spherical_coords;

	theta = atan2(p.tuple.units.x, p.tuple.units.z);
	vec = vector(p.tuple.units.x, p.tuple.units.y, p.tuple.units.z);
	radius = magnitude(vec);
	phi = acos(p.tuple.units.y / radius);

	raw_u = theta / (2 * M_PI);
	spherical_coords.u = 1 - (raw_u + 0.5);
	spherical_coords.v = 1 - phi / M_PI;
	return (spherical_coords);
}

t_uv_map	planar_map(t_tuple p)
{
	t_uv_map map;
	map.u = fmod(p.tuple.units.x, 1);
	if (map.u < 0)
		map.u += 1;
	map.v = fmod(p.tuple.units.z, 1);
	if (map.v < 0)
		map.v += 1;
	return (map);
}

t_uv_map	cylindrical_map(t_tuple p)
{
	t_fl		theta;
	t_fl		raw_u;
	t_uv_map	map;

	theta = atan2(p.tuple.units.x, p.tuple.units.z);
	raw_u = theta / (2 * M_PI);
	map.u = 1 - (raw_u + 0.5);
	map.v = fmod(p.tuple.units.y, 1);
	if (map.v < 0)
		map.v += 1;
	//if map.v > 1 - do something;
	return (map);

}

t_tuple	uv_pattern_at(t_uv_pattern *pattern, t_fl u, t_fl v)
{
	uint32_t u2;
	uint32_t v2;

	u2 = floor(u * pattern->width);
	v2 = floor(v * pattern->height);
	if ((u2 + v2) % 2 == 0)
		return (pattern->colour_a);
	else
		return (pattern->colour_b);
}

t_tuple	new_pattern_at(t_texture_map map, t_object_type type, t_tuple p)
{
	if (type == OBJECT_PLANE)
		map.map = planar_map(p);
	else if(type == OBJECT_SPHERE)
		map.map = spherical_map(p);
	// else if(type == OBJECT_CONE)
	// 	map.map = conical_map(p);
	else if(type == OBJECT_CYLINDER)
		map.map = cylindrical_map(p);
	// else if(type == OBJECT_CUBE)
	// 	map.map = cube_map(p);
	else
		handle_errors("incorrect object type");

	return (uv_pattern_at(&map.pattern, map.map.u, map.map.v));
}
