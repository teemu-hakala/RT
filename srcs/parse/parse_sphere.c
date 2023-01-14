











#include "RT.h"

t_object	sphere_prototype(void)
{
	return ((t_object){
		.object.sphere = (t_sphere)
		{
			.origin = default_origin(),
			.transform = default_transform_1(),
			.material = default_material_1(),
			.appearance.pattern = default_pattern(),
			.appearance.texture = default_texture(),
		},
		.type = OBJECT_SPHERE,
		.id = object_identification()
	});
}

void	parse_sphere(t_parser *parser, t_object *shape)
{
	dispatch_find_subobject_keyword(parser, shape);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		parse_sphere(parser, shape);
	}
	else if (!find_matching_bracket(parser))
		handle_errors("sphere syntax error");
	transform_object(&shape->object.sphere.transform);
	if (shape->object.sphere.appearance.texture.type == TEXTURE_CHECKERED)
		shape->object.sphere.appearance.texture.width = \
			2 * shape->object.sphere.appearance.texture.height;
}
