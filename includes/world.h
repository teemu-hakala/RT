/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:01:50 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/12 17:19:11 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H
# include "RT.h"

typedef enum e_filter_type
{
	SEPIA = 0,
	NEGATIVE = 1,
	GRAYSCALE = 2,
	FILTER_COUNT,
	FILTER_NONE
}		t_filter_type;

typedef struct s_quadratic
{
	t_fl	a;
	t_fl	b;
	t_fl	c;
	t_fl	discriminant;
	t_fl	res_1;
	t_fl	res_2;
}				t_quadratic;

typedef struct s_intersect
{
	t_fl			time;
	t_object		*shape;
	t_material		material;
	t_appearance	appearance;
	t_transform		transform;
	t_uv_map (*f)(t_tuple *);
}				t_intersect;

typedef struct s_hit
{
	t_intersect	intersection;
	t_comp		computations;
	int			hit_check;
}	t_hit;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}			t_ray;

typedef struct s_world
{
	t_camera		camera;
	t_vec			lights;
	t_vec			objects;
	t_vec			intersections;
	t_hit			shadow_hit;
	t_ray			ray;
	t_ray			reflected_ray;
	t_ray			refracted_ray;
	int				lifetime;
	int				refraction_lifetime;
	t_filter_type	filter;
}	t_world;

#endif
