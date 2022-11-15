/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_subobjects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:44:56 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 12:48:48 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	plane_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, &shape->object.plane.origin,
			&shape->object.plane.transform,
			&shape->object.plane.material));
}

void	sphere_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, &shape->object.sphere.origin,
			&shape->object.sphere.transform,
			&shape->object.sphere.material));
}

void	cone_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, &shape->object.cone.origin,
			&shape->object.cone.transform,
			&shape->object.cone.material));
}

void	cylinder_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, &shape->object.cylinder.origin,
			&shape->object.cylinder.transform,
			&shape->object.cylinder.material));
}

void	dispatch_find_subobject_keyword(t_parser *parser, t_object *shape)
{
	static const t_subobject_keyword_fn	kw_fns[] = \
	{
		plane_subobject_keywords,
		sphere_subobject_keywords,
		cone_subobject_keywords,
		cylinder_subobject_keywords
	};

	return (kw_fns[shape->type - OBJECT_INDEX_OFFSET](parser, shape));
}
