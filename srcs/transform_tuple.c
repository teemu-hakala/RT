/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_tuple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:06:10 by thakala           #+#    #+#             */
/*   Updated: 2022/10/19 13:54:41 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	transform_object(t_transform *object)
{
	identity_matrix_set(&object->matrix);
	translate(&object->matrix, &object->translation);
	rotate(&object->matrix, &object->rotation);
	scale(&object->matrix, &object->scale);
	object->inverse = object->matrix;
	matrix_inversion(&object->inverse, 4);
}

void	transform_plane(t_object *plane)
{
	(void)plane;
}

void	transform_sphere(t_object *sphere)
{
	transform_object(&sphere->object.sphere.transform);
}

void	transform_cone(t_object *cone)
{
	(void)cone;
}

void	transform_cylinder(t_object *cylinder)
{
	(void)cylinder;
}

void	transform_camera(t_object *camera)
{
	(void)camera;
}

void	transform_light(t_object *light)
{
	(void)light;
}

void	transform_objects(t_objects *objects)
{
	static const t_object_transform	object_transform[] = {
		transform_plane,
		transform_sphere,
		transform_cone,
		transform_cylinder,
		transform_camera,
		transform_light};

	uint64_t						i;

	i = -1;
	while (++i < objects->count)
	{
		object_transform[objects->list[i].type](&objects->list[i]);
	}
}

/*void	transform_tuple(t_tuple tuple, t_transform *actions)
{

}*/