/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_shape_subobjects.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:36:16 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 11:36:18 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

int	dispatch_find_subobject_keyword(t_parser *parser, t_object *shape)
{
	static const t_subobject_keyword_fn	kw_fns[] = \
	{
		plane_subobject_keywords,
		sphere_subobject_keywords,
		cone_subobject_keywords,
		cylinder_subobject_keywords,
		cube_subobject_keywords
	};

	return (kw_fns[shape->type](parser, shape));
}
