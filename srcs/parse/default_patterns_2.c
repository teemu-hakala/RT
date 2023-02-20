/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_patterns_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:45:49 by ikarjala          #+#    #+#             */
/*   Updated: 2023/02/12 12:47:14 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_pattern	default_perlin_noise(void)
{
	return ((t_pattern){
		.type = PATTERN_PERLIN_NOISE,
		.colour_a = hex_to_tuple_colour(COLOUR_BLACK),
		.colour_b = hex_to_tuple_colour(COLOUR_WHITE),
		.transform = default_transform_1()
	});
}
