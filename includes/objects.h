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

typedef enum e_object_type
{
	OBJECT_INDEX_OFFSET = 42,
	OBJECT_PLANE = 42,
	OBJECT_SPHERE = 43,
	OBJECT_CONE = 44,
	OBJECT_CYLINDER = 45,
	OBJECT_ERROR,
	OBJECT_NONE
}	t_object_type;

typedef struct s_field_of_view
{
	t_fl	vertical;
	t_fl	horizontal;
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

typedef struct s_comp
{
	t_fl			time;
	t_object_type	type;
	t_tuple			point;
	t_phong			vectors;
	int				inside;
}				t_comp;

typedef struct s_plane
{
	t_tuple		origin;
	t_transform	transform;
	t_tuple		normal;
	t_material	material;
	t_comp		comp;
}	t_plane;

typedef struct s_sphere
{
	t_tuple		origin;
	t_transform	transform;
	t_material	material;
	t_comp		comp;
}	t_sphere;

typedef struct s_cone
{
	t_tuple		origin;
	t_transform	transform;
	t_material	material;
	t_comp		comp;
}	t_cone;

typedef struct s_cylinder
{
	t_tuple		origin;
	t_transform	transform;
	t_fl		radius;
	t_material	material;
	t_comp		comp;
}	t_cylinder;

typedef struct s_light
{
	t_tuple		position;
	t_tuple		intensity;
	t_transform	transform;
}	t_light;

typedef struct s_canvas_size
{
	uint16_t	vertical;
	uint16_t	horizontal;
}	t_canvas;

typedef struct s_camera
{
	t_tuple		origin;
	t_transform	transform;
	t_tuple		center_of_interest;
	t_canvas	size;
	t_fl		field_of_view;
	t_fl		pixel_size;
	t_fl		half_width;
	t_fl		half_height;
	t_fl		aspect;
}	t_camera;

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

typedef t_tuple	(*t_normal_fn)(void *, t_tuple *);

typedef void	(*t_object_transform)(t_object *);

#endif
