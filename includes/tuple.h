/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:07:10 by thakala           #+#    #+#             */
/*   Updated: 2022/10/12 11:27:13 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLE_H
# define TUPLE_H
# include "RTv1.h"

enum e_tuple_type
{
	W_ID_VECTOR_0 = 0,
	W_ID_POINT_1 = 1
};

typedef double	t_fl;

enum e_coords {
	X_WIDTH = 0,
	Y_HEIGHT = 1,
	Z_DEPTH = 2,
	W_ID = 3
};

typedef struct s_units {
	t_fl	x_width;
	t_fl	y_height;
	t_fl	z_depth;
	t_fl	w_id;
}	t_units;

typedef union u_wrapper {
	t_units	tuple;
	t_fl	array[sizeof(t_units) / sizeof(t_fl)];
}	t_tuple;

#endif
