/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:47:10 by thakala           #+#    #+#             */
/*   Updated: 2022/10/10 17:24:00 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include "RTv1.h"

/* AN EXAMPLE: */

typedef struct s_field_of_view
{
	t_fl	horizontal;
	t_fl	vertical;
}	t_fov2;

typedef struct s_transform
{
	t_mtx	matrix;
	t_mtx	inverse;
	t_tuple	translation;
	t_tuple	rotation;
	t_tuple	scale;
}	t_transform;

typedef struct s_material
{
	t_fl	ambient;
	t_fl	diffuse;
	t_fl	specular;
	t_fl	shininess;
	t_tuple	colour;
	t_tuple	amb_col;
	t_tuple	dif_col;
	t_tuple	spec_col;
	t_tuple	col_mash;
}				t_material;

typedef struct s_plane
{
	t_tuple		origin;
	t_transform	transform;
	t_tuple		normal;
	t_material	material;
}	t_plane;

typedef struct s_sphere
{
	t_tuple		origin;
	t_transform	transform;
	t_material	material;
}	t_sphere;

typedef struct s_cylinder
{
	t_tuple		origin;
	t_transform	transform;
	t_fl		radius;
	t_material	material;
}	t_cylinder;

typedef struct s_cone
{
	t_tuple		origin;
	t_transform	transform;
	t_material	material;
}	t_cone;

typedef struct s_light
{
	t_tuple		origin;
	t_transform	transform;
	t_colour	intensity;
	t_fl		ambience;
}	t_light;

typedef struct s_camera
{
	t_tuple		origin;
	t_transform	transform;
	t_fov2		field_of_view;
}	t_camera;

enum	e_object_type
{
	OBJECT_PLANE = 0,
	OBJECT_SPHERE = 1,
	OBJECT_CONE = 2,
	OBJECT_CYLINDER = 3,
	OBJECT_CAMERA,
	OBJECT_LIGHT,
	OBJECT_ERROR,
	OBJECT_NONE
};

union	u_object
{
	t_plane		plane;
	t_sphere	sphere;
	t_cone		cone;
	t_cylinder	cylinder;
	t_camera	camera;
	t_light		light;
};

typedef struct s_object
{
	union u_object		object;
	enum e_object_type	type;
}	t_object;

typedef t_tuple	(*t_normal_fn)(t_object *, t_tuple *);

typedef void	(*t_object_transform)(t_object *);

typedef struct s_objects
{
	t_object	*list;
	uint64_t	count;
}	t_objects;

#endif
