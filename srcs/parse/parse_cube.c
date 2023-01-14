











#include "RT.h"

t_object	cube_prototype(void)
{
	return ((t_object){
		.object.cube = (t_cube)
		{
			.origin = default_origin(),
			.transform = default_transform_1(),
			.material = default_material_1(),
			.appearance.pattern = default_pattern(),
			.appearance.texture = default_texture(),
		},
		.type = OBJECT_CUBE,
		.id = object_identification()
	});
}

void	parse_cube(t_parser *parser, t_object *shape)
{
	dispatch_find_subobject_keyword(parser, shape);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		parse_cube(parser, shape);
	}
	else if (!find_matching_bracket(parser))
		handle_errors("cube syntax error");
	transform_object(&shape->object.cube.transform);
}
