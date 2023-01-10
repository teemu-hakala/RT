











#include "RT.h"

t_transform	plane_transform(void)
{
	t_transform	plane_transform;

	plane_transform.translation = point(0, 0, 0);
	plane_transform.rotation = point(0, 0, 0);
	plane_transform.scale = point(1, 1, 1);
	transform_object(&plane_transform);
	return (plane_transform);
}

t_object	plane_prototype(void)
{
	return ((t_object){
		.object.plane = (t_plane)
		{
			.origin = default_origin(),
			.transform = plane_transform(),
			.material = default_material_1(),
			.appearance.pattern = default_pattern(),
			.appearance.texture = default_texture(),
		},
		.type = OBJECT_PLANE
	});
}

void	parse_plane(t_parser *parser, t_object *shape)
{
	dispatch_find_subobject_keyword(parser, shape);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		parse_plane(parser, shape);
	}
	else if (!find_matching_bracket(parser))
		handle_errors("plane syntax error");
	transform_object(&shape->object.plane.transform);
}
