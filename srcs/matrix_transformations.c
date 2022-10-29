#include "RTv1.h"

/*
	transformations that return a point t_tuple
*/

t_tuple	translate_tuple(t_tuple *tuple, t_tuple *transform)
{
	t_mtx	temp;

	identity_matrix_set(&temp);
	temp.array[4 * 0 + 3] = transform->array[X];
	temp.array[4 * 1 + 3] = transform->array[Y];
	temp.array[4 * 2 + 3] = transform->array[Z];
	return (matrix_tuple_multi(&temp, tuple));
}

t_tuple	scale_tuple(t_tuple *tuple, t_tuple *transform)
{
	t_mtx	temp;

	identity_matrix_set(&temp);
	temp.array[4 * 0 + 0] = transform->array[X];
	temp.array[4 * 1 + 1] = transform->array[Y];
	temp.array[4 * 2 + 2] = transform->array[Z];
	return (matrix_tuple_multi(&temp, tuple));
}

t_tuple	rot_x_tuple(t_tuple *tuple, t_fl angle)
{
	t_mtx	temp;

	identity_matrix_set(&temp);
	temp.array[4 * 1 + 1] = cos(angle);
	temp.array[4 * 1 + 2] = -sin(angle);
	temp.array[4 * 2 + 1] = sin(angle);
	temp.array[4 * 2 + 2] = cos(angle);
	return (matrix_tuple_multi(&temp, tuple));
}

t_tuple	rot_y_tuple(t_tuple *tuple, t_fl angle)
{
	t_mtx	temp;

	identity_matrix_set(&temp);
	temp.array[4 * 0 + 0] = cos(angle);
	temp.array[4 * 0 + 2] = sin(angle);
	temp.array[4 * 2 + 0] = -sin(angle);
	temp.array[4 * 2 + 2] = cos(angle);
	return (matrix_tuple_multi(&temp, tuple));
}

t_tuple	rot_z_tuple(t_tuple *tuple, t_fl angle)
{
	t_mtx	temp;

	identity_matrix_set(&temp);
	temp.array[4 * 0 + 0] = cos(angle);
	temp.array[4 * 0 + 1] = -sin(angle);
	temp.array[4 * 1 + 0] = sin(angle);
	temp.array[4 * 1 + 1] = cos(angle);
	return (matrix_tuple_multi(&temp, tuple));
}

/*
	transformations that modify t_object directly (write via the mtx reference)
*/

void	translate(t_mtx *mtx, t_tuple *transform)
{
	t_mtx	translation;

	identity_matrix_set(&translation);
	translation.array[4 * 0 + 3] = transform->array[X];
	translation.array[4 * 1 + 3] = transform->array[Y];
	translation.array[4 * 2 + 3] = transform->array[Z];
	matrix_multi_square(mtx, &translation, 4);
}

void	scale(t_mtx *mtx, t_tuple *transform)
{
	t_mtx	scaling;

	identity_matrix_set(&scaling);
	scaling.array[4 * 0 + 0] = transform->array[X];
	scaling.array[4 * 1 + 1] = transform->array[Y];
	scaling.array[4 * 2 + 2] = transform->array[Z];
	matrix_multi_square(mtx, &scaling, 4);
}

void	rotate(t_mtx *mtx, t_tuple *rotations)
{
	rot_x(mtx, rotations->tuple.rotation.x_wid_lat_pitch);
	rot_y(mtx, rotations->tuple.rotation.y_hei_vert_yaw);
	rot_z(mtx, rotations->tuple.rotation.z_dep_long_roll);
}

void	rot_x(t_mtx *mtx, t_fl angle)
{
	t_mtx	rotate_x;

	identity_matrix_set(&rotate_x);
	rotate_x.array[4 * 1 + 1] = cos(angle);
	rotate_x.array[4 * 1 + 2] = -sin(angle);
	rotate_x.array[4 * 2 + 1] = sin(angle);
	rotate_x.array[4 * 2 + 2] = cos(angle);
	matrix_multi_square(mtx, &rotate_x, 4);
}

void	rot_y(t_mtx *mtx, t_fl angle)
{
	t_mtx	rotate_y;

	identity_matrix_set(&rotate_y);
	rotate_y.array[4 * 0 + 0] = cos(angle);
	rotate_y.array[4 * 0 + 2] = sin(angle);
	rotate_y.array[4 * 2 + 0] = -sin(angle);
	rotate_y.array[4 * 2 + 2] = cos(angle);
	matrix_multi_square(mtx, &rotate_y, 4);
}

void	rot_z(t_mtx *mtx, t_fl angle)
{
	t_mtx	rotate_y;

	identity_matrix_set(&rotate_y);
	rotate_y.array[4 * 0 + 0] = cos(angle);
	rotate_y.array[4 * 0 + 1] = -sin(angle);
	rotate_y.array[4 * 1 + 0] = sin(angle);
	rotate_y.array[4 * 1 + 1] = cos(angle);
	matrix_multi_square(mtx, &rotate_y, 4);
}

t_ray	ray_translation(t_ray ray, t_tuple transform)
{
	t_ray	new;

	new.origin = translate_tuple(&ray.origin, &transform);
	new.direction = ray.direction;
	return (new);
}

t_ray	ray_scale(t_ray ray, t_tuple transform)
{
	t_ray	new;

	new.origin = scale_tuple(&ray.origin, &transform);
	new.direction = scale_tuple(&ray.direction, &transform);
	return (new);
}

t_ray	ray_transform(t_ray *ray, t_mtx *transform)
{
	t_ray	result;

	result.origin = matrix_tuple_multi(transform, &ray->origin);
	result.direction = matrix_tuple_multi(transform, &ray->direction);
	return (result);
}

/*t_mtx	*translate(t_tuple tuple, t_mtx *transform, t_tuple vector)
{
	transform->array[3] = vector.tuple.x_width;
	transform->array[7] = vector.tuple.y_height;
	transform->array[11] = vector.tuple.z_depth;
	return (transform);
}*/

