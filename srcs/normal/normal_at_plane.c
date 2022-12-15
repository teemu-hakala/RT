#include "RT.h"

t_tuple	normal_at_plane(void *plane, t_tuple *point_at)
{
	t_tuple	obj_normal;
	t_tuple	world_normal;
	t_mtx	transposed_inverse;

	(void)point_at;
	obj_normal = vector(0, 1, 0);
	transposed_inverse = \
		transpose_matrix(&((t_plane *)plane)->transform.inverse);
	world_normal = matrix_tuple_multi(&transposed_inverse, &obj_normal);
	world_normal.tuple.units.w = 0;
	return (normalize(world_normal));
}
