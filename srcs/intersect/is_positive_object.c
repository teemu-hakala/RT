











#include "RT.h"

t_material	*is_positive_object(t_object *shape)
{
	t_material	*material;

	material = get_material(shape);
	if (material->negative == false)
		return (material);
	return (NULL);
}
