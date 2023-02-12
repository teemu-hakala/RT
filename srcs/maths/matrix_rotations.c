/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:33:24 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/12 16:58:25 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

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

void	rotate(t_mtx *mtx, t_tuple *rotations)
{
	rot_x(mtx, rotations->tuple.rotation.x_wid_lat_pitch);
	rot_y(mtx, rotations->tuple.rotation.y_hei_vert_yaw);
	rot_z(mtx, rotations->tuple.rotation.z_dep_long_roll);
}
