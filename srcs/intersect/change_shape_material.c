











#include "RT.h"

void	change_shape_material(t_object *recipient, t_object *giver)
{
	static const t_change_shape_material_function \
		change_shape_material[] = {
			plane_shapeshift,
			sphere_shapeshift,
			cone_shapeshift,
			cylinder_shapeshift,
			cube_shapeshift
		};
	change_shape_material[recipient->type - OBJECT_INDEX_OFFSET](recipient,
		giver);
}
