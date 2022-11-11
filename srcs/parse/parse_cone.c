#include "RTv1.h"

t_object cone_prototype()
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
	parser->c += 7;
	find_colon(parser);
	find_open_bracket(parser);
	*shape = cone_prototype();
	if (find_matching_bracket(parser))
		return ;
	else
	{
		while (dispatch_find_subobject_keyword(parser, shape))
			parse_cone(parser, cone);

		if (!find_matching_bracket(parser))
			handle_errors("syntax error");
	}
}