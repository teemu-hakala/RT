/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:07:10 by thakala           #+#    #+#             */
/*   Updated: 2022/10/11 16:08:07 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLE_H
# define TUPLE_H
# include "RTv1.h"

typedef double	t_fl;

enum e_coords {
	X_WIDTH = 0,
	Y_HEIGHT = 1,
	Z_DEPTH = 2,
	W_ID = 3
};

typedef struct s_coords {
	t_fl	x_width;
	t_fl	y_height;
	t_fl	z_depth;
	t_fl	w_id;
}	t_coords;

typedef union u_wrapper {
	// struct s_tuple {
	// 	t_fl	x_width;
	// 	t_fl	y_height;
	// 	t_fl	z_depth;
	// 	t_fl	w_id;
	// }	tuple;
	t_coords	tuple;
	t_fl		array[sizeof(t_coords) / sizeof(t_fl)];
}	t_tuple;

#endif
