/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:03:46 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/13 16:11:46 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RTv1.h"

t_fl	*translate(t_tuple tuple, t_fl x, t_fl y, t_fl z)
{
	t_fl	**temp;
	t_fl	*a;

	temp = identity_matrix();
	if (temp)
	{
		temp[0][3] = x;
		temp[1][3] = y;
		temp[2][3] = z;
		a = matrix_tuple_multi(temp, tuple);
		ft_memdelarray((void *)temp, 4);
	}
	return (a);
}

/*t_mtx_4	*translate(t_tuple tuple, t_mtx_4 *transform, t_tuple vector)
{
	transform->array[3] = vector.tuple.x_width;
	transform->array[7] = vector.tuple.y_height;
	transform->array[11] = vector.tuple.z_depth;
	return (transform);
}*/

t_fl	*scale(t_tuple tuple, t_fl x, t_fl y, t_fl z)
{
	t_fl	**temp;
	t_fl	*a;

	temp = identity_matrix();
	if (temp)
	{
		temp[0][0] = x;
		temp[1][1] = y;
		temp[2][2] = z;
		a = matrix_tuple_multi(temp, tuple);
		ft_memdelarray((void *)temp, 4);
	}
	return (a);
}

t_fl	*rot_x(t_tuple tuple, t_fl angle)
{
	t_fl	**temp;
	t_fl	*a;

	temp = identity_matrix();
	if (temp)
	{
		temp[1][1] = cos(angle);
		temp[1][2] = -sin(angle);
		temp[2][1] = sin(angle);
		temp[2][2] = cos(angle);
		a = matrix_tuple_multi(temp, tuple);
		ft_memdelarray((void *)temp, 4);
	}
	return (a);
}

t_fl	*rot_y(t_tuple tuple, t_fl angle)
{
	t_fl	**temp;
	t_fl	*a;

	temp = identity_matrix();
	if (temp)
	{
		temp[0][0] = cos(angle);
		temp[0][2] = sin(angle);
		temp[2][0] = -sin(angle);
		temp[2][2] = cos(angle);
		a = matrix_tuple_multi(temp, tuple);
		ft_memdelarray((void *)temp, 4);
	}
	return (a);
}

t_fl	*rot_z(t_tuple tuple, t_fl angle)
{
	t_fl	**temp;
	t_fl	*a;

	temp = identity_matrix();
	if (temp)
	{
		temp[0][0] = cos(angle);
		temp[0][1] = -sin(angle);
		temp[1][0] = sin(angle);
		temp[1][1] = cos(angle);
		a = matrix_tuple_multi(temp, tuple);
		ft_memdelarray((void *)temp, 4);
	}
	return (a);
}
