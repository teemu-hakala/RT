











#include "RT.h"

int	plane_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser,
			&shape->object.plane.transform,
			&shape->object.plane.material, &shape->object.plane.pattern));
}

int	sphere_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser,
			&shape->object.sphere.transform,
			&shape->object.sphere.material, &shape->object.sphere.pattern));
}

int	cone_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser,
			&shape->object.cone.transform,
			&shape->object.cone.material, &shape->object.cone.pattern));
}

int	cylinder_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser,
			&shape->object.cylinder.transform,
			&shape->object.cylinder.material, &shape->object.cylinder.pattern));
}

int	dispatch_find_subobject_keyword(t_parser *parser, t_object *shape)
{
	static const t_subobject_keyword_fn	kw_fns[] = \
	{
		plane_subobject_keywords,
		sphere_subobject_keywords,
		cone_subobject_keywords,
		cylinder_subobject_keywords
	};

	return (kw_fns[shape->type - OBJECT_INDEX_OFFSET](parser, shape));
}
