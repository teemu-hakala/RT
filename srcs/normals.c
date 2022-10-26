#include "RTv1.h"

t_tuple	normal_at_plane(t_plane *object, t_tuple *point_at)
{
	(void)object;
	(void)point_at;
	return (vector(1, 0, 0));
}

t_tuple	normal_at_sphere(t_sphere *sphere, t_tuple *point_at)
{
	t_tuple	obj_point;
	t_tuple	obj_normal;
	t_tuple	world_normal;
	t_mtx	transposed_inverse;

	obj_point = matrix_tuple_multi(&sphere->transform.inverse, point_at);
	obj_normal = tuple_sub(obj_point, sphere->origin);
	transposed_inverse = transpose_matrix(&sphere->transform.inverse);
	world_normal = matrix_tuple_multi(&transposed_inverse, &obj_normal);
	world_normal.tuple.units.w = 0;
	return (normalize(world_normal));
}

t_tuple	normal_at_cone(t_cone *object, t_tuple *point_at)
{
	(void)object;
	(void)point_at;
	return (vector(1, 0, 0));
}

t_tuple	normal_at_cylinder(t_cylinder *object, t_tuple *point_at)
{
	(void)object;
	(void)point_at;
	return (vector(1, 0, 0));
}

t_tuple	normal_at(void *object, t_object_type type, t_tuple *point)
{
	static const t_normal_fn	normals[] = {
		normal_at_plane,
		normal_at_sphere,
		normal_at_cone,
		normal_at_cylinder};

	return (normals[type](object, point));
}
