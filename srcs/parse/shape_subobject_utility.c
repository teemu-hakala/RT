#include "RT.h"

int	plane_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, &shape->object.plane.origin,
			&shape->object.plane.transform,
			&shape->object.plane.material));
}

int	sphere_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, &shape->object.sphere.origin,
			&shape->object.sphere.transform,
			&shape->object.sphere.material));
}

int	cone_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, &shape->object.cone.origin,
			&shape->object.cone.transform,
			&shape->object.cone.material));
}

int	cylinder_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, &shape->object.cylinder.origin,
			&shape->object.cylinder.transform,
			&shape->object.cylinder.material));
}

int	cube_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, &shape->object.cube.origin,
			&shape->object.cube.transform,
			&shape->object.cube.material));
}
