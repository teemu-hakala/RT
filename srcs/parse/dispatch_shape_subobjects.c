











#include "RT.h"

int	dispatch_find_subobject_keyword(t_parser *parser, t_object *shape)
{
	static const t_subobject_keyword_fn	kw_fns[] = \
	{
		plane_subobject_keywords,
		sphere_subobject_keywords,
		cone_subobject_keywords,
		cylinder_subobject_keywords,
		cube_subobject_keywords
	};

	return (kw_fns[shape->type](parser, shape));
}
