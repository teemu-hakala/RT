#include "RTv1.h"

t_object	cone_prototype(void)
{
	return ((t_object){
		.object.cone = (t_cone)
		{
			.origin = default_origin(),
			.transform = default_transform(),
			.material = default_material(),
			.min = -INFINITY,
			.max = INFINITY,
			.closed = false
		},
		.type = OBJECT_CONE
	});
}

void	parse_cone(t_parser *parser, t_object *shape)
{
	dispatch_find_subobject_keyword(parser, shape);
	parser->c += ft_clear_whitespace(parser->string);
	if (parser->string[++parser->c] == ',')
		parse_cone(parser, shape);
	else if (!find_matching_bracket(parser))
		handle_errors("cone syntax error");
}