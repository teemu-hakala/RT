#include "RT.h"

void	prepare_plane(t_world *world)
{
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations);
}

void	prepare_sphere(t_world *world)
{
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations);
}

void	prepare_cone(t_world *world)
{
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations);
}

void	prepare_cylinder(t_world *world)
{
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations);
}

void	prepare_cube(t_world *world)
{
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations);
}