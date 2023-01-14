











#include "RT.h"


t_material	*plane_get_material(t_object *shape)
{
	return (&shape->object.plane.material);
}

t_material	*sphere_get_material(t_object *shape)
{
	return (&shape->object.sphere.material);
}

t_material	*cone_get_material(t_object *shape)
{
	return (&shape->object.cone.material);
}

t_material	*cylinder_get_material(t_object *shape)
{
	return (&shape->object.cylinder.material);
}

t_material	*cube_get_material(t_object *shape)
{
	return (&shape->object.cube.material);
}

