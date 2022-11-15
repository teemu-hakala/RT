/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:13:10 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 10:13:12 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_pattern_colours	set_pattern_colours(t_tuple a, t_tuple b)
{
	return ((t_pattern_colours){
		.a = a,
		.b = b
	});
}

void	none_at(t_material *material, t_tuple *point)
{
	(void)point;
	material->final_colour = material->init_colour;
}

void	striped_at(t_material *material, t_tuple *point)
{
	if (fmod(floor(point->tuple.units.x), 2) == 0)
		material->final_colour = material->pattern.colour.a;
	else
		material->final_colour = material->pattern.colour.b;
}

void	checkered_at(t_material *material, t_tuple *point)
{
	if (fmod((floor(point->tuple.units.x) + floor(point->tuple.units.y) + \
		floor(point->tuple.units.z)), 2) == 0)
		material->final_colour = material->pattern.colour.a;
	else
		material->final_colour = material->pattern.colour.b;
}

void	circle_at(t_material *material, t_tuple *point)
{
	t_fl	temp;

	temp = sqrt((point->tuple.units.x * point->tuple.units.x) + \
		(point->tuple.units.z * point->tuple.units.z));
	if (fmod(floor(temp), 2) == 0)
		material->final_colour = material->pattern.colour.a;
	else
		material->final_colour = material->pattern.colour.b;
}

void	gradient_at(t_material *material, t_tuple *point)
{
	t_fl	x_fraction;

	x_fraction = fabs(point->tuple.units.x) - floor(fabs(point->tuple.units.x));
	material->final_colour = tuple_add(material->pattern.colour.a, \
	colour_scale(tuple_sub(material->pattern.colour.b, \
	material->pattern.colour.a),x_fraction));
}

void	pattern_at(t_material *material, t_tuple *point, t_transform transform)
{
	t_tuple	object_space;
	t_tuple	pattern_space;

	object_space = matrix_tuple_multi(&transform.inverse, point);
	pattern_space = matrix_tuple_multi(&material->pattern.transform.inverse, &object_space);
	static const t_pattern_at_fn	patterns[] = {
		none_at,
		striped_at,
		checkered_at,
		circle_at,
		gradient_at};

	return (patterns[material->pattern.type](material, &pattern_space));
}