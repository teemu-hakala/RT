











#include "RT.h"

void	plane_shapeshift(t_object *recipient, t_object *giver)
{
	recipient->object.plane.material = *get_material(giver);
}

void	sphere_shapeshift(t_object *recipient, t_object *giver)
{
	recipient->object.sphere.material = *get_material(giver);
}

void	cone_shapeshift(t_object *recipient, t_object *giver)
{
	recipient->object.cone.material = *get_material(giver);
}

void	cylinder_shapeshift(t_object *recipient, t_object *giver)
{
	recipient->object.cylinder.material = *get_material(giver);
}

void	cube_shapeshift(t_object *recipient, t_object *giver)
{
	recipient->object.cube.material = *get_material(giver);
}
