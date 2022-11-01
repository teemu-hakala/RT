#include "RTv1.h"

t_object	cylinder(t_tuple origin, t_transform transform, t_material material)
{
	return ((t_object)
		{
			.object.cylinder = (t_cylinder)
			{
				.origin = origin,
				.transform = transform,
				.radius = 1,
				.material = material,
				.comp = (t_comp){},
				.min = -INFINITY,
				.max = INFINITY
			},
			.type = OBJECT_CYLINDER
		}
	);
}
