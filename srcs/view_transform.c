











#include "RT.h"

t_transform	default_transform(void)
{
	return (
		(t_transform)
		{
			.matrix = identity_matrix(),
			.inverse = identity_matrix(),
			.translation = point(0, 0, 0),
			.rotation = point(0, 0, 0),
			.scale = point(1, 1, 1)
		}
	);
}

static int	tuple_nearly_equals(t_tuple tuple_a, t_tuple tuple_b)
{
	t_tuple	diff;

	diff = tuple_sub(tuple_a, tuple_b);
	return (-TUPLE_EPSILON < diff.array[X] && diff.array[X] < TUPLE_EPSILON
		&& - TUPLE_EPSILON < diff.array[Y] && diff.array[Y] < TUPLE_EPSILON
		&& - TUPLE_EPSILON < diff.array[Z] && diff.array[Z] < TUPLE_EPSILON);
}

t_mtx	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple	forward;
	t_tuple	left;
	t_tuple	up_n;
	t_tuple	true_up;
	t_mtx	orientation;

	forward = normalize(tuple_sub(to, from));
	up_n = normalize(up);
	left = cross_product(forward, up_n);
	if (tuple_nearly_equals(left, vector(0, 0, 0)))
		left = cross_product(forward, vector(0, 0, 1));
	true_up = cross_product(left, forward);
	orientation = (t_mtx){
		.tuple_rows = {\
	(t_quad_tuple){left.tuple.units.x, left.tuple.units.y, \
		left.tuple.units.z, 0.0}, \
	(t_quad_tuple){true_up.tuple.units.x, true_up.tuple.units.y, \
		true_up.tuple.units.z, 0.0}, \
	(t_quad_tuple){-forward.tuple.units.x, -forward.tuple.units.y, \
		-forward.tuple.units.z, 0.0}, \
	(t_quad_tuple){0.0, 0.0, 0.0, 1.0} \
		}};
	translate(&orientation, &(t_tuple){.tuple.units = {-from.tuple.units.x, \
		-from.tuple.units.y, -from.tuple.units.z, POINT_1}});
	return (orientation);
}
