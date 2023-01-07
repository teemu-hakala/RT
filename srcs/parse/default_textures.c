/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:49:47 by deelliot          #+#    #+#             */
/*   Updated: 2022/12/12 15:36:08 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_texture	default_texture(void)
{
	return ((t_texture){
		.type = TEXTURE_NONE,
		.colour_a = hex_to_tuple_colour(COLOUR_HOT_PINK),
		.colour_b = hex_to_tuple_colour(COLOUR_HOT_PINK),
		.transform = default_transform_1(),
		.fd = -1
	});
}

t_texture	default_checkered_texture(void)
{
	return ((t_texture){
		.type = TEXTURE_CHECKERED,
		.width = 4,
		.height = 4,
		.colour_a = hex_to_tuple_colour(COLOUR_BLUE),
		.colour_b = hex_to_tuple_colour(COLOUR_WHITE),
		.transform = default_transform_2(),
		.fd = -1
	});
}

t_texture	default_align_check(void)
{
	return ((t_texture){
		.type = TEXTURE_ALIGN_CHECK,
		.face = 0,
		.main[0] = hex_to_tuple_colour(COLOUR_HOT_PINK),
		.ul[0] = hex_to_tuple_colour(COLOUR_HOT_PINK),
		.ur[0] = hex_to_tuple_colour(COLOUR_HOT_PINK),
		.bl[0] = hex_to_tuple_colour(COLOUR_HOT_PINK),
		.br[0] = hex_to_tuple_colour(COLOUR_HOT_PINK),
		.transform = default_transform_2(),
		.fd = -1
	});
}

t_texture	default_external(void)
{
	return ((t_texture){
		.type = TEXTURE_EXTERNAL,
		.transform = default_transform_1(),
		.fd = -1,
		.image.height = 0,
		.image.width = 0,
		.image.max_value = 0
	});
}
