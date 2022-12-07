











#include "RTv1.h"

t_tuple	object_to_world_space(t_mtx *inverse, t_tuple obj_space)
{
	t_mtx	transposed_inverse;
	t_tuple	world_space;

	transposed_inverse = transpose_matrix(inverse);
	world_space = matrix_tuple_multi(&transposed_inverse, &obj_space);
	world_space.tuple.units.w = 0;
	return (world_space);
}
