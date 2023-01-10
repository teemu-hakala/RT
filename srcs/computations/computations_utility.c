#include "RT.h"

void	prepare_plane(t_world *world, t_ray ray)
{
	world->hit.computations.reflective = \
		world->hit.intersection.shape->object.plane.material.reflectiveness;
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations, ray);
}

void	prepare_sphere(t_world *world, t_ray ray)
{
	world->hit.computations.reflective = \
		world->hit.intersection.shape->object.sphere.material.reflectiveness;
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations, ray);
}

void	prepare_cone(t_world *world, t_ray ray)
{
	world->hit.computations.reflective = \
		world->hit.intersection.shape->object.cone.material.reflectiveness;
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations, ray);
}

void	prepare_cylinder(t_world *world, t_ray ray)
{
	world->hit.computations.reflective = \
		world->hit.intersection.shape->object.cylinder.material.reflectiveness;
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations, ray);
}

void	prepare_cube(t_world *world, t_ray ray)
{
	world->hit.computations.reflective = \
		world->hit.intersection.shape->object.cube.material.reflectiveness;
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations, ray);
}
