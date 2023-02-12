/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:53:46 by thakala           #+#    #+#             */
/*   Updated: 2023/02/12 17:41:58 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_tuple	apply_grayscale(t_tuple original)
{
	t_tuple	temp;

	temp.tuple.colour.r = (original.tuple.colour.r + original.tuple.colour.g \
		+ original.tuple.colour.b) / 3;
	temp.tuple.colour.g = (original.tuple.colour.r + original.tuple.colour.g \
		+ original.tuple.colour.b) / 3;
	temp.tuple.colour.b = (original.tuple.colour.r + original.tuple.colour.g \
		+ original.tuple.colour.b) / 3;
	return (temp);
}

t_tuple	apply_negative(t_tuple original)
{
	t_tuple	temp;

	temp.tuple.colour.r = (1 - original.tuple.colour.r);
	temp.tuple.colour.g = (1 - original.tuple.colour.g);
	temp.tuple.colour.b = (1 - original.tuple.colour.b);
	return (temp);
}

t_tuple	apply_sepia(t_tuple original)
{
	t_tuple	temp;

	temp.tuple.colour.r = (original.tuple.colour.r * 0.393) + \
		(original.tuple.colour.g * 0.769) + \
		(original.tuple.colour.b * 0.189);
	temp.tuple.colour.g = (original.tuple.colour.r * 0.349) + \
		(original.tuple.colour.g * 0.686) + \
		(original.tuple.colour.b * 0.168);
	temp.tuple.colour.b = (original.tuple.colour.r * 0.272) + \
		(original.tuple.colour.g * 0.534) + \
		(original.tuple.colour.b * 0.131);
	return (temp);
}

t_tuple	apply_filter(t_world *world, t_tuple colour)
{
	if (world->filter == SEPIA)
		return (apply_sepia(colour));
	if (world->filter == NEGATIVE)
		return (apply_negative(colour));
	if (world->filter == GRAYSCALE)
		return (apply_grayscale(colour));
	else
		return (colour);
}
