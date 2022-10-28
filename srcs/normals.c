#include "RTv1.h"

t_tuple	normal_at_plane(void *plane, t_tuple *point_at)
{
	(void)plane;
	(void)point_at;
	return (vector(1, 0, 0));
}

t_tuple	normal_at_sphere(void *sphere, t_tuple *point_at)
{
	t_tuple	obj_point;
	t_tuple	obj_normal;
	t_tuple	world_normal;
	t_mtx	transposed_inverse;

	obj_point = \
		matrix_tuple_multi(&((t_sphere *)sphere)->transform.inverse, point_at);
	obj_normal = tuple_sub(obj_point, ((t_sphere *)sphere)->origin);


	transposed_inverse = \
		transpose_matrix(&((t_sphere *)sphere)->transform.inverse);
	world_normal = matrix_tuple_multi(&transposed_inverse, &obj_normal);
	world_normal.tuple.units.w = 0;
	return (normalize(world_normal));
}

t_tuple	normal_at_cone(void *cone, t_tuple *point_at)
{
	(void)cone;
	(void)point_at;
	return (vector(1, 0, 0));
}

t_tuple	normal_at_cylinder(void *cylinder, t_tuple *point_at)
{
	(void)cylinder;
	(void)point_at;
	return (vector(1, 0, 0));
}

t_tuple	normal_at(void *object, t_tuple *point)
{
	static const t_normal_fn	normals[] = {
		normal_at_plane,
		normal_at_sphere,
		normal_at_cone,
		normal_at_cylinder};

	return (normals[((t_object *)object)->type \
		- OBJECT_INDEX_OFFSET](object, point));
}
