/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:38:38 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/18 14:51:25 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static void	rot_x(t_mtx *mtx, t_fl angle)
{
	t_mtx	rotate_x;

	identity_matrix_set(&rotate_x);
	rotate_x.array[4 * 1 + 1] = cos(angle);
	rotate_x.array[4 * 1 + 2] = -sin(angle);
	rotate_x.array[4 * 2 + 1] = sin(angle);
	rotate_x.array[4 * 2 + 2] = cos(angle);
	matrix_multi_square(mtx, &rotate_x, 4);
}

static void	rot_y(t_mtx *mtx, t_fl angle)
{
	t_mtx	rotate_y;

	identity_matrix_set(&rotate_y);
	rotate_y.array[4 * 0 + 0] = cos(angle);
	rotate_y.array[4 * 0 + 2] = sin(angle);
	rotate_y.array[4 * 2 + 0] = -sin(angle);
	rotate_y.array[4 * 2 + 2] = cos(angle);
	matrix_multi_square(mtx, &rotate_y, 4);
}

static void	rot_z(t_mtx *mtx, t_fl angle)
{
	t_mtx	rotate_z;

	identity_matrix_set(&rotate_z);
	rotate_z.array[4 * 0 + 0] = cos(angle);
	rotate_z.array[4 * 0 + 1] = -sin(angle);
	rotate_z.array[4 * 1 + 0] = sin(angle);
	rotate_z.array[4 * 1 + 1] = cos(angle);
	matrix_multi_square(mtx, &rotate_z, 4);
}

void	rotate(t_mtx *mtx, t_tuple *rotations)
{
	rot_x(mtx, rotations->tuple.rotation.x_wid_lat_pitch);
	rot_y(mtx, rotations->tuple.rotation.y_hei_vert_yaw);
	rot_z(mtx, rotations->tuple.rotation.z_dep_long_roll);
}
