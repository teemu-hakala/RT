/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:01:23 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 12:01:27 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERNS_H
# define PATTERNS_H
# include "RT.h"
# include "objects.h"

typedef enum e_text_type
{
	TEXTURE_NONE = 0,
	TEXTURE_CHECKERED = 1,
	TEXTURE_ALIGN_CHECK = 2,
	TEXTURE_EXTERNAL = 3
}	t_text_type;

typedef enum e_pattern_type
{
	PATTERN_NONE = 0,
	PATTERN_VERTICAL_STRIPES = 1,
	PATTERN_HORIZONTAL_STRIPES = 2,
	PATTERN_CIRCLES = 3,
	PATTERN_GRADIENT = 4,
	PATTERN_SIMPLE_CHECKERED = 5
}	t_type;

typedef enum e_cube_face
{
	FACE_FRONT = 0,
	FACE_BACK = 1,
	FACE_LEFT = 2,
	FACE_RIGHT = 3,
	FACE_UP = 4,
	FACE_DOWN = 5,
}	t_face;


typedef struct s_uv_map
{
	t_fl	u;
	t_fl	v;
}			t_uv_map;

#endif