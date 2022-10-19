/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:27:24 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/19 16:09:29 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_tuple reflect(t_tuple *input, t_tuple *normal)
{
	t_tuple result;
	t_fl temp;

	temp = 2 * dot_product(input, normal);
	normal->tuple.units.x *= temp;
	normal->tuple.units.y *= temp;
	normal->tuple.units.z *= temp;
	result = (tuple_sub(input, normal));
	return (result);
}
