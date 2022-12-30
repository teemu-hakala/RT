
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

t_uv_map	conical_map(t_tuple p)
{
	t_fl		theta;
	t_fl		raw_u;
	t_uv_map	map;

	theta = atan2(p.tuple.units.x, p.tuple.units.z);
	raw_u = theta / (2 * M_PI);
	map.u = 1 - (raw_u + 0.5);
	map.v = fmod((2 * p.tuple.units.y + 1), 1); //no idea if this is correct
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
	else if(type == OBJECT_CONE)
		map.map = conical_map(p);
	else if(type == OBJECT_CYLINDER)
		map.map = cylindrical_map(p);
	// else if(type == OBJECT_CUBE)
	// 	map.map = cube_map(p);
	else
		handle_errors("incorrect object type");

	return (uv_pattern_at(&map.pattern, map.map.u, map.map.v));
}

t_uv_pattern	align_check(t_tuple main, t_tuple ul, t_tuple ur, t_tuple bl, t_tuple br)
{

}

void	test_pattern_at(void)
{
	t_fl	width = 2;
	t_fl	height = 2;
	t_tuple	colour_a = point(0, 0, 0);
	t_tuple	colour_b = point(1, 1, 1);
	t_uv_pattern pattern = uv_checkers(width, height, colour_a, colour_b);
	t_tuple colour;

	colour = uv_pattern_at(&pattern, 1, 1);
	printf("%0.2f, %0.2f, %0.2f", colour.array[0], colour.array[1], colour.array[2]);
}

void	test_spherical_mapping(void)
{
	t_uv_map spherical_coords;

	spherical_coords = spherical_map(point(0, 0, -1));
	printf("u: %0.2f, v: %0.2f\n", spherical_coords.u, spherical_coords.v);
	spherical_coords = spherical_map(point(1, 0, 0));
	printf("u: %0.2f, v: %0.2f\n", spherical_coords.u, spherical_coords.v);
	spherical_coords = spherical_map(point(0, 0, 1));
	printf("u: %0.2f, v: %0.2f\n", spherical_coords.u, spherical_coords.v);
	spherical_coords = spherical_map(point(-1, 0, 0));
	printf("u: %0.2f, v: %0.2f\n", spherical_coords.u, spherical_coords.v);
	spherical_coords = spherical_map(point(0, 1, 0));
	printf("u: %0.2f, v: %0.2f\n", spherical_coords.u, spherical_coords.v);
	spherical_coords = spherical_map(point(0, -1, 0));
	printf("u: %0.2f, v: %0.2f\n", spherical_coords.u, spherical_coords.v);
	spherical_coords = spherical_map(point(0.707, 0.707, 0));
	printf("u: %0.2f, v: %0.2f\n", spherical_coords.u, spherical_coords.v);
}

void	test_planar_mapping(void)
{
	t_uv_map planar_coords;
	t_tuple	point_1 = point(0.25, 0, 0.5);
	t_tuple	point_2 = point(0.25, 0, -0.25);
	t_tuple	point_3 = point(0.25, 0.5, -0.25);
	t_tuple	point_4 = point(1.25, 0, 0.5);
	t_tuple	point_5 = point(0.25, 0, -1.75);
	t_tuple	point_6 = point(1, 0, -1);
	t_tuple	point_7 = point(0, 0, 0);

	planar_coords = planar_map(point_1);
	printf("u: %0.2f, v: %0.2f\n", planar_coords.u, planar_coords.v);
	planar_coords = planar_map(point_2);
	printf("u: %0.2f, v: %0.2f\n", planar_coords.u, planar_coords.v);
	planar_coords = planar_map(point_3);
	printf("u: %0.2f, v: %0.2f\n", planar_coords.u, planar_coords.v);
	planar_coords = planar_map(point_4);
	printf("u: %0.2f, v: %0.2f\n", planar_coords.u, planar_coords.v);
	planar_coords = planar_map(point_5);
	printf("u: %0.2f, v: %0.2f\n", planar_coords.u, planar_coords.v);
	planar_coords = planar_map(point_6);
	printf("u: %0.2f, v: %0.2f\n", planar_coords.u, planar_coords.v);
	planar_coords = planar_map(point_7);
	printf("u: %0.2f, v: %0.2f\n", planar_coords.u, planar_coords.v);

}

void	test_cylindrical_mapping(void)
{
	t_uv_map cylindrical_coords;
	t_tuple point_1 = point(0, 0, -1);
	t_tuple point_2 = point(0, 0.5, -1);
	t_tuple point_3 = point(0, 1, -1);
	t_tuple point_4 = point(0.70711, 0.5, -0.70711);
	t_tuple point_5 = point(1, 0.5, 0);
	t_tuple point_6 = point(0.70711, 0.5, 0.70711);
	t_tuple point_7 = point(0, -0.25, 1);
	t_tuple point_8 = point(-0.70711, 0.5, 0.70711);
	t_tuple point_9 = point(-1, 1.25, 0);
	t_tuple point_10 = point(-0.70711, 0.5, -0.70711);

	cylindrical_coords = cylindrical_map(point_1);
	printf("u: %0.3f, v: %0.3f\n", cylindrical_coords.u, cylindrical_coords.v);
	cylindrical_coords = cylindrical_map(point_2);
	printf("u: %0.3f, v: %0.3f\n", cylindrical_coords.u, cylindrical_coords.v);
	cylindrical_coords = cylindrical_map(point_3);
	printf("u: %0.3f, v: %0.3f\n", cylindrical_coords.u, cylindrical_coords.v);
	cylindrical_coords = cylindrical_map(point_4);
	printf("u: %0.3f, v: %0.3f\n", cylindrical_coords.u, cylindrical_coords.v);
	cylindrical_coords = cylindrical_map(point_5);
	printf("u: %0.3f, v: %0.3f\n", cylindrical_coords.u, cylindrical_coords.v);
	cylindrical_coords = cylindrical_map(point_6);
	printf("u: %0.3f, v: %0.3f\n", cylindrical_coords.u, cylindrical_coords.v);
	cylindrical_coords = cylindrical_map(point_7);
	printf("u: %0.3f, v: %0.3f\n", cylindrical_coords.u, cylindrical_coords.v);
	cylindrical_coords = cylindrical_map(point_8);
	printf("u: %0.3f, v: %0.3f\n", cylindrical_coords.u, cylindrical_coords.v);
	cylindrical_coords = cylindrical_map(point_9);
	printf("u: %0.3f, v: %0.3f\n", cylindrical_coords.u, cylindrical_coords.v);
	cylindrical_coords = cylindrical_map(point_10);
	printf("u: %0.3f, v: %0.3f\n", cylindrical_coords.u, cylindrical_coords.v);
}

void	test_spherical_texture_mapping(void)
{
	t_texture_map map;
	t_tuple colour;
	t_tuple	point_1 = point(0.4315, 0.4670, 0.7719);
	t_tuple	point_2 = point(0.4315, 0.4670, 0.7719);
	t_tuple	point_3 = point(-0.9654, 0.2552, -0.0534);
	t_tuple	point_4 = point(0.1039, 0.7090, 0.6975);
	t_tuple	point_5 = point(-0.4986, -0.7856, -0.3663);
	t_tuple	point_6 = point(-0.0317, -0.9395, 0.3411);
	t_tuple	point_7 = point(0.4809, -0.7721, 0.4154);
	t_tuple	point_8 = point(0.0285, -0.9612, -0.2745);
	t_tuple	point_9 = point(-0.5734, -0.2162, -0.7903);
	t_tuple	point_10 = point(0.7688, -0.1470, 0.6223);
	t_tuple	point_11 = point(-0.7652, 0.2175, 0.6060);


	map.pattern = uv_checkers(16, 8, point(0, 0, 0), point(1, 1, 1));

	colour = new_pattern_at(map, 43, point_1);
	printf("%0f, %0f, %0f\n", colour.array[0], colour.array[1], colour.array[2]);
	colour = new_pattern_at(map, 43, point_2);
	printf("%0f, %0f, %0f\n", colour.array[0], colour.array[1], colour.array[2]);
	colour = new_pattern_at(map, 43, point_3);
	printf("%0f, %0f, %0f\n", colour.array[0], colour.array[1], colour.array[2]);
	colour = new_pattern_at(map, 43, point_4);
	printf("%0f, %0f, %0f\n", colour.array[0], colour.array[1], colour.array[2]);
	colour = new_pattern_at(map, 43, point_5);
	printf("%0f, %0f, %0f\n", colour.array[0], colour.array[1], colour.array[2]);
	colour = new_pattern_at(map, 43, point_6);
	printf("%0f, %0f, %0f\n", colour.array[0], colour.array[1], colour.array[2]);
	colour = new_pattern_at(map, 43, point_7);
	printf("%0f, %0f, %0f\n", colour.array[0], colour.array[1], colour.array[2]);
	colour = new_pattern_at(map, 43, point_8);
	printf("%0f, %0f, %0f\n", colour.array[0], colour.array[1], colour.array[2]);
	colour = new_pattern_at(map, 43, point_9);
	printf("%0f, %0f, %0f\n", colour.array[0], colour.array[1], colour.array[2]);
	colour = new_pattern_at(map, 43, point_10);
	printf("%0f, %0f, %0f\n", colour.array[0], colour.array[1], colour.array[2]);
	colour = new_pattern_at(map, 43, point_11);
	printf("%0f, %0f, %0f\n", colour.array[0], colour.array[1], colour.array[2]);
}

void	test_align_check(void)
{
	t_tuple main = point(1, 1, 1);
    t_tuple ul = point(1, 0, 0);
    t_tuple ur = point(1, 1, 0);
    t_tuple bl = point(0, 1, 0);
    t_tuple br = point(0, 1, 1);
	t_uv_pattern pattern = align_check(main, ul, ur, bl, br);
	t_tuple colour;

	t_uv_map map_1 = {0.5, 0.5};
	t_uv_map map_2 = {0.1, 0.9};
	t_uv_map map_3 = {0.9, 0.9};
	t_uv_map map_4 = {0.1, 0.1};
	t_uv_map map_5 = {0.9, 0.1};
	colour = uv_pattern_at(&pattern, map_1.u, map_1.v);
	printf("%0.f, %0.f, %0.f\n", colour.array[0], colour.array[1], colour.array[2]);
	colour = uv_pattern_at(&pattern, map_2.u, map_2.v);
	printf("%0.f, %0.f, %0.f\n", colour.array[0], colour.array[1], colour.array[2]);
	colour = uv_pattern_at(&pattern, map_3.u, map_3.v);
	printf("%0.f, %0.f, %0.f\n", colour.array[0], colour.array[1], colour.array[2]);
	colour = uv_pattern_at(&pattern, map_4.u, map_4.v);
	printf("%0.f, %0.f, %0.f\n", colour.array[0], colour.array[1], colour.array[2]);
	colour = uv_pattern_at(&pattern, map_5.u, map_5.v);
	printf("%0.f, %0.f, %0.f\n", colour.array[0], colour.array[1], colour.array[2]);
}

void	test_uv_mapping(void)
{
	// test_pattern_at();
	// test_spherical_mapping();
	// test_spherical_texture_mapping();
	//test_planar_mapping();
	//test_cylindrical_mapping();
	//test_align_check();
}

int main(void)
{
	test_uv_mapping();
	return (0);
}
