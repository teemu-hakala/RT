











#include "RT.h"

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
