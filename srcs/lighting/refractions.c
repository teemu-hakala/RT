








/* Snell's law: n1sin(ti) = n2sin(tr)
	ti = angle of incidence
	tr = angle of refraction
	n1 = refractive index of current object
	n2 = refractive index of next object

Snell's law asserts that n1/n2 = sin α2/sin α1.
Because the ratio n1/n2 is a constant for any given wavelength of light,
the ratio of the two sines is also a constant for any angle. */

/* total internal reflection when light enters a new medium with a
lower refractive index than the current medium, at a sufficiently acute angle,
the light ray will reflect off the interface instead of passing through it */

#include "RT.h"

int	check_for_total_internal_reflection(t_comp *computations)
{
	t_fl	n_ratio;
	t_fl	cos_i;
	t_fl	sin2_t;

	n_ratio = computations->n1 / computations->n2;
	cos_i = dot_product(computations->vectors.eye, \
		computations->vectors.surface_normal);
	sin2_t = (n_ratio * n_ratio) * (1 - (cos_i * cos_i));
	if (sin2_t > 1)
		return (true);
	return (false);
}

t_tuple	refracted_colour(t_world *world, t_comp *computations)
{
	t_tuple	refracted_colour;
	t_fl	transparency;
	t_fl	n_ratio;
	t_fl	cos_i;
	t_fl	sin2_t;
	t_fl	cos_t;
	t_tuple	direction;

	refracted_colour = point(0, 0, 0);
	transparency = world->hit.intersection.material.transparency;
	n_ratio = computations->n1 / computations->n2;
	cos_i = dot_product(computations->vectors.eye, \
		computations->vectors.surface_normal);
	sin2_t = (n_ratio * n_ratio) * (1 - (cos_i * cos_i));
	cos_t = sqrt(1 - sin2_t);
	direction = tuple_sub(tuple_scale(computations->vectors.surface_normal,\
		(n_ratio * (cos_i - cos_t))), \
		tuple_scale(computations->vectors.eye, n_ratio));
	if (world->refraction_lifetime-- <= 0)
 		return (refracted_colour);
	if (transparency < EPSILON)
		return (refracted_colour);
	if (check_for_total_internal_reflection(computations) == true)
		return (refracted_colour);
	else
		world->refracted_ray = ray(computations->under_point, direction);
		return (point(1, 1, 1));
	refracted_colour = colour_at(world, world->refracted_ray);
	return (tuple_scale(refracted_colour, transparency));
}
