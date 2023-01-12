/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_patterns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:49:47 by deelliot          #+#    #+#             */
/*   Updated: 2023/01/09 16:17:53 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_pattern	default_vertical_stripe_pattern(void)
{
	return ((t_pattern){
		.type = PATTERN_VERTICAL_STRIPES,
		.colour_a = hex_to_tuple_colour(COLOUR_YELLOW),
		.colour_b = hex_to_tuple_colour(COLOUR_WHITE),
		.transform = default_transform_2()
	});
}

t_pattern	default_horizontal_stripe_pattern(void)
{
	return ((t_pattern){
		.type = PATTERN_HORIZONTAL_STRIPES,
		.colour_a = hex_to_tuple_colour(COLOUR_YELLOW),
		.colour_b = hex_to_tuple_colour(COLOUR_WHITE),
		.transform = default_transform_2()
	});
}

t_pattern	default_gradient_pattern(void)
{
	return ((t_pattern){
		.type = PATTERN_GRADIENT,
		.colour_a = hex_to_tuple_colour(COLOUR_WHITE),
		.colour_b = hex_to_tuple_colour(COLOUR_RED),
		.transform = default_transform_1()
	});
}

t_pattern	default_ring_pattern(void)
{
	return ((t_pattern){
		.type = PATTERN_CIRCLES,
		.colour_a = hex_to_tuple_colour(COLOUR_BLACK),
		.colour_b = hex_to_tuple_colour(COLOUR_WHITE),
		.transform = default_transform_2()
	});
}

t_pattern	default_simple_checkered_pattern(void)
{
	return ((t_pattern){
		.type = PATTERN_SIMPLE_CHECKERED,
		.colour_a = hex_to_tuple_colour(COLOUR_BLUE),
		.colour_b = hex_to_tuple_colour(COLOUR_WHITE),
		.transform = default_transform_2()
	});
}

