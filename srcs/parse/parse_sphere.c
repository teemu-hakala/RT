#include "RTv1.h"

t_object	sphere_prototype(void)
{
	return ((t_object){
		.object.sphere = (t_sphere)
		{
			.origin = default_origin(),
			.transform = default_transform(),
			.material = default_material_1()
		},
		.type = OBJECT_SPHERE
	});
}

void	parse_sphere(t_parser *parser, t_object *shape)
{
	dispatch_find_subobject_keyword(parser, shape);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[++parser->c] == ',')
		parse_sphere(parser, shape);
	else if (!find_matching_bracket(parser))
		handle_errors("sphere syntax error");
}