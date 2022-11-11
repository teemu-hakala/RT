#include "RTv1.h"

t_object cylinder_prototype()
{
	return ((t_object){
		.object.cylinder = (t_cylinder)
		{
			.origin = default_origin(),
			.transform = default_transform(),
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
	parser->c += 7;
	find_colon(parser);
	find_open_bracket(parser);
	*shape = cylinder_prototype();
	if (find_matching_bracket(parser))
		return ;
	else
	{
		while (dispatch_find_subobject_keyword(parser, shape))
			parse_cylinder(parser, cylinder);
		if ()
		if (!find_matching_bracket(parser))
			handle_errors("syntax error");
	}
}