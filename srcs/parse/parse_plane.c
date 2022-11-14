#include "RTv1.h"

t_transform	plane_transform(void)
{
	t_transform	plane_transform;

	plane_transform.translation = point(0, 0, 0);
	plane_transform.rotation = point(M_PI_2, 0, -M_PI_4);
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
			.material = default_material_1()
		},
		.type = OBJECT_PLANE
	});
}

void	parse_plane(t_parser *parser, t_object *shape)
{
	dispatch_find_subobject_keyword(parser, shape);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[++parser->c] == ',')
		parse_plane(parser, shape);
	else if (!find_matching_bracket(parser))
		handle_errors("plane syntax error");
}