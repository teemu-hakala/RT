











#include "RT.h"

t_object	cone_prototype(void)
{
	return ((t_object){
		.object.cone = (t_cone)
		{
			.origin = default_origin(),
			.transform = default_transform_1(),
			.material = default_material_1(),
			.appearance.pattern = default_pattern(),
			.appearance.texture = default_texture(),
			.min = -INFINITY,
			.max = INFINITY,
			.closed = false
		},
		.type = OBJECT_CONE,
		.id = object_identification()
	});
}

void	cone_continued(t_object *shape)
{
	transform_object(&shape->object.cone.transform);
	if (shape->object.cone.appearance.texture.type == TEXTURE_CHECKERED)
		shape->object.cone.appearance.texture.width = \
			2 * shape->object.cone.appearance.texture.height;
	shape->object.cone.material.negative = false;
}

void	parse_cone(t_parser *parser, t_object *shape)
{
	if (dispatch_find_subobject_keyword(parser, shape))
	{
		parser->c += ft_clear_whitespace(&parser->string[parser->c]);
		if (parser->string[parser->c] == ',')
		{
			parser->c++;
			parse_cone(parser, shape);
		}
		else if (!find_matching_bracket(parser))
			handle_errors("cone syntax error");
	}
	else if (cone_and_cylinder_objects(parser, shape))
	{
		parser->c += ft_clear_whitespace(&parser->string[parser->c]);
		if (parser->string[parser->c] == ',')
		{
			parser->c++;
			parse_cone(parser, shape);
		}
		else if (!find_matching_bracket(parser))
			handle_errors("cone syntax error");
	}
	else if (!find_matching_bracket(parser))
		handle_errors("cone syntax error");
	cone_continued(shape);
}
