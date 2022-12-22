#include "RT.h"

void	prepare_plane(t_world *world)
{
	world->hit.computations.reflective = \
		world->hit.intersection.shape->object.plane.material.reflectiveness;
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations);
}

void	prepare_sphere(t_world *world)
{
	world->hit.computations.reflective = \
		world->hit.intersection.shape->object.sphere.material.reflectiveness;
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations);
}

void	prepare_cone(t_world *world)
{
	world->hit.computations.reflective = \
		world->hit.intersection.shape->object.cone.material.reflectiveness;
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations);
}

void	prepare_cylinder(t_world *world)
{
	world->hit.computations.reflective = \
		world->hit.intersection.shape->object.cylinder.material.reflectiveness;
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations);
}

void	prepare_cube(t_world *world)
{
	world->hit.computations.reflective = \
		world->hit.intersection.shape->object.cube.material.reflectiveness;
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations);
}