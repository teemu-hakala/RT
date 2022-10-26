#include "RTv1.h"

t_tuple	point(t_fl x, t_fl y, t_fl z)
{
	return ((t_tuple){
		.tuple.units.x = x,
		.tuple.units.y = y,
		.tuple.units.z = z,
		.tuple.units.w = POINT_1
	});
}

t_tuple	vector(t_fl x, t_fl y, t_fl z)
{
	return ((t_tuple){
		.tuple.units.x = x,
		.tuple.units.y = y,
		.tuple.units.z = z,
		.tuple.units.w = VECTOR_0
	});
}

t_tuple	colour(t_fl a, t_fl r, t_fl g, t_fl b)
{
	return ((t_tuple){
		.tuple.colour.a = a,
		.tuple.colour.r = r,
		.tuple.colour.g = g,
		.tuple.colour.b = b
	});
}

t_tuple	tuple_add(t_tuple a, t_tuple b)
{
	return ((t_tuple){
		.tuple.units.x = a.tuple.units.x + b.tuple.units.x,
		.tuple.units.y = a.tuple.units.y + b.tuple.units.y,
		.tuple.units.z = a.tuple.units.z + b.tuple.units.z,
		.tuple.units.w = a.tuple.units.w + b.tuple.units.w
	});
}

t_tuple	tuple_sub(t_tuple a, t_tuple b)
{
	return ((t_tuple){
		.tuple.units.x = a.tuple.units.x - b.tuple.units.x,
		.tuple.units.y = a.tuple.units.y - b.tuple.units.y,
		.tuple.units.z = a.tuple.units.z - b.tuple.units.z,
		.tuple.units.w = a.tuple.units.w - b.tuple.units.w
	});
}

t_tuple	tuple_scale(t_tuple a, t_fl scalar)
{
	return ((t_tuple){
		.tuple.units.x = a.tuple.units.x * scalar,
		.tuple.units.y = a.tuple.units.y * scalar,
		.tuple.units.z = a.tuple.units.z * scalar
	});
}

t_tuple	colour_scale(t_tuple a, t_fl scalar)
{
	return ((t_tuple){
		.tuple.colour.a = a.tuple.colour.a * scalar,
		.tuple.colour.r = a.tuple.colour.r * scalar,
		.tuple.colour.g = a.tuple.colour.g * scalar,
		.tuple.colour.b = a.tuple.colour.b * scalar
	});
}

t_tuple	tuple_multi(t_tuple a, t_tuple b)
{
	return ((t_tuple){
		.tuple.units.x = a.tuple.units.x * b.tuple.units.x,
		.tuple.units.y = a.tuple.units.y * b.tuple.units.y,
		.tuple.units.z = a.tuple.units.z * b.tuple.units.z,
		.tuple.units.w = a.tuple.units.w * b.tuple.units.w
	});
}

t_tuple	tuple_div(t_tuple a, t_fl scalar)
{
	return ((t_tuple){
		.tuple.units.x = a.tuple.units.x / scalar,
		.tuple.units.y = a.tuple.units.y / scalar,
		.tuple.units.z = a.tuple.units.z / scalar,
		.tuple.units.w = a.tuple.units.w / scalar
	});
}

t_fl	magnitude(t_tuple a)
{
	if (sizeof(t_fl) == sizeof(long double))
		return (sqrtl(((a.tuple.units.x * a.tuple.units.x)
					+ (a.tuple.units.y * a.tuple.units.y)
					+ (a.tuple.units.z * a.tuple.units.z))));
	else
		return (sqrt(((a.tuple.units.x * a.tuple.units.x)
					+ (a.tuple.units.y * a.tuple.units.y)
					+ (a.tuple.units.z * a.tuple.units.z))));
}

t_tuple	normalize(t_tuple a)
{
	t_fl	mag;

	mag = magnitude(a);
	if (mag != 0)
		return (tuple_div(a, mag));
	return (vector(0, 0, 0));
}

/* the dot product calculates the cosine angle between two vectors
the smaller the dot product, the larger the angle between vectors*/

/* vector length = sqrt of the dot product of the vector itself */

t_fl	dot_product(t_tuple a, t_tuple b)
{
	return ((a.tuple.units.x * b.tuple.units.x)
		+ (a.tuple.units.y * b.tuple.units.y)
		+ (a.tuple.units.z * b.tuple.units.z)
		+ (a.tuple.units.w * b.tuple.units.w)); // is it necessary to calculate the w axis?
}

t_tuple	cross_product(t_tuple a, t_tuple b)
{
	return ((t_tuple){
		.tuple.units.x = a.tuple.units.y * b.tuple.units.z
		- a.tuple.units.z * b.tuple.units.y,
		.tuple.units.y = a.tuple.units.z * b.tuple.units.x
		- a.tuple.units.x * b.tuple.units.z,
		.tuple.units.z = a.tuple.units.x * b.tuple.units.y
		- a.tuple.units.y * b.tuple.units.x
	});
}
