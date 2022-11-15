/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_tuple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:02:57 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 10:03:02 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	transform_object(t_transform *object)
{
	identity_matrix_set(&object->matrix);
	translate(&object->matrix, &object->translation);
	rotate(&object->matrix, &object->rotation);
	scale(&object->matrix, &object->scale);
	object->inverse = object->matrix;
	matrix_inversion(&object->inverse, 4);
}

