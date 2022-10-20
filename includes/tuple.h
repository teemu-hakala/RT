/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:07:10 by thakala           #+#    #+#             */
/*   Updated: 2022/10/20 16:44:50 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLE_H
# define TUPLE_H

# include "RTv1.h"

typedef double	t_fl;

enum e_tuple_type
{
	PRISTINE = -1,
	VECTOR_0 = 0,
	POINT_1 = 1
};

enum e_tuple_component_indices {
	X = 0,
	Y = 1,
	Z = 2,
	W = 3
};

typedef struct s_units_of_axial_length
{
	t_fl	x;
	t_fl	y;
	t_fl	z;
	t_fl	w;
}	t_units;

typedef struct s_colour_channels
{
	t_fl	a;
	t_fl	r;
	t_fl	g;
	t_fl	b;
}	t_colour;

typedef struct s_units_of_axial_rotation
{
	t_fl	x_wid_lat_pitch;
	t_fl	y_hei_vert_yaw;
	t_fl	z_dep_long_roll;
	t_fl	w_id;
}	t_rotation;

typedef union u_tuple_alias
{
	t_units		units;
	t_colour	colour;
	t_rotation	rotation;
}	t_tuple_alias;

typedef union u_wrapper
{
	t_tuple_alias	tuple;
	t_fl			array[sizeof(t_units) / sizeof(t_fl)];
}	t_tuple;

#endif
