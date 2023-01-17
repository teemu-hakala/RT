











#include "RT.h"

void	prepare_computations(t_world *world, t_ray ray)
{
	static const t_computation_fn	\
			precompute_shape[] = {
		prepare_plane,
		prepare_sphere,
		prepare_cone,
		prepare_cylinder,
		prepare_cube
	};

	precompute_shape[world->hit.intersection.shape->type]
		(world, ray);
}
