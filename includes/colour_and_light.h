/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_and_light.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:34:04 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/27 10:57:40 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOUR_AND_LIGHT_H
# define COLOUR_AND_LIGHT_H

# include "RTv1.h"

enum e_colour
{
	COLOUR_RED = 0x00FF0000,
	COLOUR_GREEN = 0x0000FF00,
	COLOUR_BLUE = 0x000000FF,
	COLOUR_BLACK = 0x00000000,
	COLOUR_WHITE = 0x00FFFFFF,
	COLOUR_TURQOUISE = 0x40E0D0U
};

typedef struct s_phong
{
	t_tuple	eye;
	t_tuple	light;
	t_tuple	surface_normal;
	t_tuple	reflection;
}				t_phong;

#endif