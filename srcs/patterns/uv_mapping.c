#include "RT.h"

t_uv_map	spherical_map(t_tuple *p)
{
	t_fl		theta;
	t_tuple		vec;
	t_fl		radius;
	t_fl		phi;
	t_fl		raw_u;
	t_uv_map	map;

	theta = atan2(p->tuple.units.x, p->tuple.units.z);
	vec = vector(p->tuple.units.x, p->tuple.units.y, p->tuple.units.z);
	radius = magnitude(vec);
	phi = acos(p->tuple.units.y / radius);

	raw_u = theta / (2 * M_PI);
	map.u = 1 - (raw_u + 0.5);
	map.v = 1 - phi / M_PI;
	if (map.v > 1 || map.v < 0)
		printf("v = %f\n", map.v);
	if (map.u > 1 || map.u < 0)
		printf("u = %f\n", map.u);
	return (map);
}

t_uv_map	planar_map(t_tuple *p)
{
	t_uv_map map;
	map.u = fmod(p->tuple.units.x, 1);
	if (map.u < 0)
		map.u += 1;
	map.v = fmod(p->tuple.units.z, 1);
	if (map.v < 0)
		map.v += 1;
	if (map.v > 1 || map.v < 0)
		printf("v = %f\n", map.v);
	if (map.u > 1 || map.u < 0)
		printf("u = %f\n", map.u);
	return (map);
}

t_uv_map	cylindrical_map(t_tuple *p)
{
	t_fl		theta;
	t_fl		raw_u;
	t_uv_map	map;

	theta = atan2(p->tuple.units.x, p->tuple.units.z);
	raw_u = theta / (2 * M_PI);
	map.u = 1 - (raw_u + 0.5);
	map.v = fmod(p->tuple.units.y, 1);
	if (map.v < 0)
		map.v += 1;
	if (map.v > 1 || map.v < 0)
		printf("v = %f\n", map.v);
	if (map.u > 1 || map.u < 0)
		printf("u = %f\n", map.u);
	return (map);
}

t_uv_map	conical_map(t_tuple *p)
{
	t_fl		theta;
	t_fl		raw_u;
	t_uv_map	map;

	theta = atan2(p->tuple.units.x, p->tuple.units.z);
	raw_u = theta / (2 * M_PI);
	map.u = 1 - (raw_u + 0.5);
	map.v = fmod((2 * p->tuple.units.y + 1), 1); //no idea if this is correct
	if (map.v < 0)
		map.v += 1;
	if (map.v > 1 || map.v < 0)
		printf("v = %f\n", map.v);
	if (map.u > 1 || map.u < 0)
		printf("u = %f\n", map.u);
	return (map);
}
