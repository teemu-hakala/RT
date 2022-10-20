/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_and_light.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:34:04 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/19 17:02:19 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOUR_AND_LIGHT_H
# define COLOUR_AND_LIGHT_H

# include "RTv1.h"

enum e_colour
{
	COLOUR_RED = 0x00FF0000
};

typedef struct s_pt_light
{
	t_tuple		position;
	t_tuple		intensity;
}				t_pt_light;

typedef struct s_phong
{
	t_tuple	eye_vector;
	t_tuple	light_vector;
	t_tuple	surface_normal;
	t_tuple	reflection_vector;
}				t_phong;


#endif