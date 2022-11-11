#include "RTv1.h"

t_object sphere_prototype()
{
	return ((t_object){
		.object.sphere = (t_sphere)
		{
			.origin = default_origin(),
			.transform = default_transform(),
			.material = default_material()
		},
		.type = OBJECT_SPHERE
	});
}

void	parse_sphere(t_parser *parser, t_object *shape)
{
	parser->c += 7;
	find_colon(parser);
	find_open_bracket(parser);
	*shape = sphere_prototype();
	if (find_matching_bracket(parser))
		return ;
	else
	{
		while (dispatch_find_subobject_keyword(parser, shape))
			parse_sphere(parser, sphere);
		if (!find_matching_bracket(parser))
			handle_errors("syntax error");
	}
}