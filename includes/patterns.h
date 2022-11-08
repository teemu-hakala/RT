/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:32:36 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/08 15:40:01 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERNS_H
# define PATTERNS_H
# include "RTv1.h"

typedef enum e_pattern_type
{
	PATTERN_NONE = 0,
	PATTERN_STRIPE = 1,
	PATTERN_CHECKERED = 2,
	PATTERN_CIRCLES = 3,
	PATTERN_GRADIENT = 4
}	t_pattern_type;

typedef struct s_pattern_colours
{
	t_tuple	a;
	t_tuple	b;
}				t_pattern_colours;

#endif