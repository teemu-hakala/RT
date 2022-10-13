/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:07:10 by thakala           #+#    #+#             */
/*   Updated: 2022/10/13 17:17:35 by deelliot         ###   ########.fr       */
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



enum e_coords {
	X_WIDTH = 0,
	Y_HEIGHT = 1,
	Z_DEPTH = 2,
	W_ID = 3
};

typedef struct s_units {
	t_fl	x; //_width;
	t_fl	y; //_height;
	t_fl	z; //_depth;
	t_fl	w; //_id;
}	t_units;

typedef union u_wrapper {
	t_units	tuple;
	t_fl	array[sizeof(t_units) / sizeof(t_fl)];
}	t_tuple;

#endif
