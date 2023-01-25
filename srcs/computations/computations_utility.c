#include "RT.h"

void	prepare_plane(t_world *world, t_ray ray)
{
	prepare_object(world, &world->hit.intersection.shape, \
		&world->hit.computations, ray);
}

void	prepare_sphere(t_world *world, t_ray ray)
{
	prepare_object(world, &world->hit.intersection.shape, \
		&world->hit.computations, ray);
}

void	prepare_cone(t_world *world, t_ray ray)
{
	prepare_object(world, &world->hit.intersection.shape, \
		&world->hit.computations, ray);
}

void	prepare_cylinder(t_world *world, t_ray ray)
{
	prepare_object(world, &world->hit.intersection.shape, \
		&world->hit.computations, ray);
}

void	prepare_cube(t_world *world, t_ray ray)
{
	prepare_object(world, &world->hit.intersection.shape, \
		&world->hit.computations, ray);
}
