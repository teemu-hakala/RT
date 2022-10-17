/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_tuple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:06:10 by thakala           #+#    #+#             */
/*   Updated: 2022/10/17 16:18:13 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*static const t_transformation_fn	transformations[] = {
	NULL, translate, rot_x, NULL, rot_y, NULL, NULL, NULL, rot_z,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, scale
};*/

void	transform_object(t_object *shape, t_transform *actions)
{
	identity_matrix_set(&shape->object.transform.matrix.resultant);
	translate(&shape->object.transform.matrix.resultant);
	rotate(&shape->object.transform.matrix.resultant);
	scale(&shape->object.transform.matrix.resultant);
	matrix_inversion(&shape->object.transform.matrix.inverse, \
		&shape->object.transform.matrix.resultant);
}

/*void	transform_tuple(t_tuple tuple, t_transform *actions)
{
	
}*/