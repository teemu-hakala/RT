#include "RT.h"

int	plane_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser,
			&shape->object.plane.transform,
			&shape->object.plane.material, &shape->object.plane.appearance));
}

int	sphere_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser,
			&shape->object.sphere.transform,
			&shape->object.sphere.material, &shape->object.sphere.appearance));
}

int	cone_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser,
			&shape->object.cone.transform,
			&shape->object.cone.material, &shape->object.cone.appearance));
}

int	cylinder_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser,
			&shape->object.cylinder.transform,
			&shape->object.cylinder.material, &shape->object.cylinder.appearance));
}

int	cube_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser,
			&shape->object.cube.transform,
			&shape->object.cube.material, &shape->object.cylinder.appearance));
}
