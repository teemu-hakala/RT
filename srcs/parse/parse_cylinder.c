#include "RTv1.h"

t_object	cylinder_prototype(void)
{
	return ((t_object){
		.object.cylinder = (t_cylinder)
		{
			.origin = default_origin(),
			.transform = default_transform_1(),
			.material = default_material(),
			.min = -INFINITY,
			.max = INFINITY,
			.closed = false
		},
		.type = OBJECT_CYLINDER
	});
}

void	parse_cylinder(t_parser *parser, t_object *shape)
{
	dispatch_find_subobject_keyword(parser, shape);
	parser->c += ft_clear_whitespace(parser->string);
	if (parser->string[++parser->c] == ',')
		parse_cylinder(parser, shape);
	else if (!find_matching_bracket(parser))
		handle_errors("cylinder syntax error");
}