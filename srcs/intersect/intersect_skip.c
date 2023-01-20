











#include "RT.h"

void	plane_intersect_if(t_ray ray, void *object, t_world *world)
{
	if ((world->camera.shutter.count == 0 && \
		!((t_plane *)object)->movement.active) || \
		(world->camera.shutter.count != 0 && \
		((t_plane *)object)->movement.active))
		plane_intersection(ray, object, world);
}

void	sphere_intersect_if(t_ray ray, void *object, t_world *world)
{
	if ((world->camera.shutter.count == 0 && \
		!((t_sphere *)object)->movement.active) || \
		(world->camera.shutter.count != 0 && \
		((t_sphere *)object)->movement.active))
		sphere_intersection(ray, object, world);
}

void	cone_intersect_if(t_ray ray, void *object, t_world *world)
{
	if ((world->camera.shutter.count == 0 && \
		!((t_cone *)object)->movement.active) || \
		(world->camera.shutter.count != 0 && \
		((t_cone *)object)->movement.active))
		cone_intersection(ray, object, world);
}

void	cylinder_intersect_if(t_ray ray, void *object, t_world *world)
{
	if ((world->camera.shutter.count == 0 && \
		!((t_cylinder *)object)->movement.active) || \
		(world->camera.shutter.count != 0 && \
		((t_cylinder *)object)->movement.active))
		cylinder_intersection(ray, object, world);
}

void	cube_intersect_if(t_ray ray, void *object, t_world *world)
{
	if ((world->camera.shutter.count == 0 && \
		!((t_cube *)object)->movement.active) || \
		(world->camera.shutter.count != 0 && \
		((t_cube *)object)->movement.active))
		cube_intersection(ray, object, world);
}
