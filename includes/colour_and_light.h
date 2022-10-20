/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_and_light.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:34:04 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/20 16:49:51 by deelliot         ###   ########.fr       */
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

typedef struct s_pt_light
{
	t_tuple		position;
	t_colour	intensity;
}				t_pt_light;

typedef struct s_phong
{
	t_tuple	eye;
	t_tuple	light;
	t_tuple	surface_normal;
	t_tuple	reflection;
}				t_phong;


#endif