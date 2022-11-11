#include "RTv1.h"

t_object plane_prototype()
{
	return ((t_object){
		.object.plane = (t_plane)
		{
			.origin = default_origin(),
			.transform = default_transform(),
			.material = default_material()
		},
		.type = OBJECT_PLANE
	});
}

void	parse_plane(t_parser *parser, t_object *shape)
{
	parser->c += 7;
	find_colon(parser);
	find_open_bracket(parser);
	*shape = plane_prototype();
	if (find_matching_bracket(parser))
		return ;
	else
	{
		while (dispatch_find_subobject_keyword(parser, shape))
			parse_plane(parser, plane);
		if (!find_matching_bracket(parser))
			handle_errors("syntax error");
	}
}