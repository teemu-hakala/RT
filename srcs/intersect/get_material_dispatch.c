











#include "RT.h"

t_material	*get_material(t_object *shape)
{
	static const t_get_material_function	\
					get_object_material[] = \
	{
		plane_get_material,
		sphere_get_material,
		cone_get_material,
		cylinder_get_material,
		cube_get_material
	};

	return (get_object_material[shape->type - OBJECT_INDEX_OFFSET](shape));
}
