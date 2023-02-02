#include "RT.h"

static t_fl	double_p2(double src)
{
	return (src * src);
}

static t_fl	double_div(double a, double b)
{
	if (a == 0 || b == 0)
		return (0.0);
	return (a / b);
}

t_fl	calc_y_rot(t_tuple a, t_tuple b)
{
	return (acos(
			double_div(
				(a.array[X] * b.array[X] + a.array[Z] * b.array[Z]),
				(sqrt((double_p2(a.array[X]) + double_p2(a.array[Z]))))
				* sqrt((double_p2(b.array[X]) + double_p2(b.array[Z]))))));
}
