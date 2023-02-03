/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:40:00 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 11:40:02 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	none_at(t_pattern *pattern, t_tuple *point, t_tuple *colour)
{
	(void)point;
	(void)pattern;
	(void)colour;
}

void	vertical_striped_at(t_pattern *pattern, \
	t_tuple *point, t_tuple *colour)
{
	if (fmod(floor(point->tuple.units.x), 2) == 0)
		*colour = pattern->colour_a;
	else
		*colour = pattern->colour_b;
}

void	horizontal_striped_at(t_pattern *pattern, \
	t_tuple *point, t_tuple *colour)
{
	if (fmod(floor(point->tuple.units.z), 2) == 0)
		*colour = pattern->colour_a;
	else
		*colour = pattern->colour_b;
}

void	circle_at(t_pattern *pattern, t_tuple *point, t_tuple *colour)
{
	if (fmod(floor(sqrt((point->tuple.units.x * point->tuple.units.x) + \
	(point->tuple.units.z * point->tuple.units.z))), 2) == 0)
		*colour = pattern->colour_a;
	else
		*colour = pattern->colour_b;
}

void	gradient_at(t_pattern *pattern, t_tuple *point, t_tuple *colour)
{
	t_fl	x_fraction;

	x_fraction = fabs(point->tuple.units.x) - floor(fabs(point->tuple.units.x));
	if (x_fraction < 0.5)
		*colour = tuple_add(pattern->colour_a, \
		tuple_scale(tuple_sub(pattern->colour_b, \
		pattern->colour_a), x_fraction));
	else
		*colour = tuple_add(pattern->colour_b, \
		tuple_scale(tuple_sub(pattern->colour_a, \
		pattern->colour_b), x_fraction));
}
