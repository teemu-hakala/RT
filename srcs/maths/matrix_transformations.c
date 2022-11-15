/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:02:46 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 16:09:43 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
	transformations that modify t_object directly (write via the mtx reference)
*/

void	translate(t_mtx *mtx, t_tuple *transform)
{
	t_mtx	translation;

	identity_matrix_set(&translation);
	translation.array[4 * 0 + 3] = transform->array[X];
	translation.array[4 * 1 + 3] = transform->array[Y];
	translation.array[4 * 2 + 3] = transform->array[Z];
	matrix_multi_square(mtx, &translation, 4);
}

void	scale(t_mtx *mtx, t_tuple *transform)
{
	t_mtx	scaling;

	identity_matrix_set(&scaling);
	scaling.array[4 * 0 + 0] = transform->array[X];
	scaling.array[4 * 1 + 1] = transform->array[Y];
	scaling.array[4 * 2 + 2] = transform->array[Z];
	matrix_multi_square(mtx, &scaling, 4);
}

