/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:36:40 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/12 14:04:10 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_object	cylinder_prototype(void)
{
	return ((t_object){
		.object.cylinder = (t_cylinder)
		{
			.origin = default_origin(),
			.transform = default_transform_1(),
			.material = default_material_1(),
			.appearance.pattern = default_pattern(),
			.appearance.texture = default_texture(),
			.radius = 1,
			.min = -INFINITY,
			.max = INFINITY,
			.closed = false
		},
		.type = OBJECT_CYLINDER
	});
}

void	cylinder_continued(t_object *shape)
{
	if (shape->object.cylinder.appearance.texture.type == TEXTURE_CHECKERED)
		shape->object.cylinder.appearance.texture.width = \
			2 * shape->object.cylinder.appearance.texture.height;
}

void	parse_cylinder(t_parser *parser, t_object *shape)
{
	if (dispatch_find_subobject_keyword(parser, shape))
	{
		parser->c += ft_clear_whitespace(&parser->string[parser->c]);
		if (parser->string[parser->c] == ',')
		{
			parser->c++;
			parse_cylinder(parser, shape);
		}
		else if (!find_matching_bracket(parser))
			handle_parser_errors("cylinder syntax error", parser);
	}
	else if (cone_and_cylinder_objects(parser, shape))
	{
		parser->c += ft_clear_whitespace(&parser->string[parser->c]);
		if (parser->string[parser->c] == ',')
		{
			parser->c++;
			parse_cylinder(parser, shape);
		}
		else if (!find_matching_bracket(parser))
			handle_parser_errors("cylinder syntax error", parser);
	}
	else if (!find_matching_bracket(parser))
		handle_parser_errors("cylinder syntax error", parser);
	cylinder_continued(shape);
}
