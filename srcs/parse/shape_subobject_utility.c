#include "RT.h"

int	plane_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser,
		&(t_object_prototype){.transform = &shape->object.plane.transform, \
			.material = &shape->object.plane.material,
			.appearance = &shape->object.plane.appearance,
			.movement = &shape->object.plane.movement}));
}

int	sphere_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser,
		&(t_object_prototype){.transform = &shape->object.sphere.transform, \
			.material = &shape->object.sphere.material,
			.appearance = &shape->object.sphere.appearance,
			.movement = &shape->object.sphere.movement}));
}

int	cone_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser,
		&(t_object_prototype){.transform = &shape->object.cone.transform, \
			.material = &shape->object.cone.material,
			.appearance = &shape->object.cone.appearance,
			.movement = &shape->object.cone.movement}));
}

int	cylinder_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, \
		&(t_object_prototype){.transform = &shape->object.cylinder.transform, \
			.material = &shape->object.cylinder.material,
			.appearance = &shape->object.cylinder.appearance,
			.movement = &shape->object.cylinder.movement}));
}

int	cube_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, \
		&(t_object_prototype){.transform = &shape->object.cube.transform, \
			.material = &shape->object.cube.material,
			.appearance = &shape->object.cube.appearance,
			.movement = &shape->object.cube.movement}));
}
