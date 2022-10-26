#include "RTv1.h"

t_object	sphere(t_tuple origin, t_transform transform, t_material material)
{
	return ((t_object)
		{
			.object.sphere = (t_sphere)
			{
				.origin = origin,
				.transform = transform,
				.material = material,
				.comp = (t_comp){.type = OBJECT_SPHERE}
			},
			.type = OBJECT_SPHERE
		}
	);
}
