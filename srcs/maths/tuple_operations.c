











#include "RTv1.h"

t_tuple	tuple_scale(t_tuple a, t_fl scalar)
{
	return ((t_tuple){
		.tuple.units.x = a.tuple.units.x * scalar,
		.tuple.units.y = a.tuple.units.y * scalar,
		.tuple.units.z = a.tuple.units.z * scalar
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



t_fl	dot_product(t_tuple a, t_tuple b)
{
	return ((a.tuple.units.x * b.tuple.units.x)
		+ (a.tuple.units.y * b.tuple.units.y)
		+ (a.tuple.units.z * b.tuple.units.z)
		+ (a.tuple.units.w * b.tuple.units.w));
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
