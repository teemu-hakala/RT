








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

typedef struct s_refraction_calculations
{
	t_fl	n_ratio;
	t_fl	cos_i;
	t_fl	sin2_t;
	t_fl	cos_t;
}				t_calc;

int	check_for_total_internal_reflection(t_calc *helper)
{
	if (helper->sin2_t > 1)
		return (true);
	return (false);
}


void	calculate_angles(t_comp *computations, t_calc *helper)
{
	helper->n_ratio = computations->n1 / computations->n2;
	helper->cos_i = dot_product(computations->vectors.eye, \
		computations->vectors.surface_normal);
	helper->sin2_t = (helper->n_ratio * helper->n_ratio) * \
		(1 - (helper->cos_i * helper->cos_i));
	helper->cos_t = sqrt(1 - helper->sin2_t);
}

t_tuple	refracted_colour(t_world *world, t_comp *computations)
{
	t_tuple	refracted_colour;
	t_fl	transparency;
	t_tuple	direction;
	t_calc	helper;

	refracted_colour = point(0, 0, 0);
	transparency = world->hit.intersection.material.transparency;
	calculate_angles(computations, &helper);
	direction = tuple_sub(tuple_scale(computations->vectors.surface_normal,\
		(helper.n_ratio * (helper.cos_i - helper.cos_t))), \
		tuple_scale(computations->vectors.eye, helper.n_ratio));
	if (world->refraction_lifetime-- <= 0)
 		return (refracted_colour);
	if (transparency < EPSILON)
		return (refracted_colour);
	if (check_for_total_internal_reflection(&helper) == true)
		return (refracted_colour);
	else
		world->refracted_ray = ray(computations->under_point, direction);
		return (point(1, 1, 1));
	refracted_colour = colour_at(world, world->refracted_ray);
	return (tuple_scale(refracted_colour, transparency));
}

t_fl	schlick(t_comp *comps)
{
	t_calc	helper;
	t_fl	reflectance;

	calculate_angles(comps, &helper);
	if (comps->n1 > comps->n2)
	{
		if (check_for_total_internal_reflection(&helper) == true)
			return (1);
		helper.cos_i = helper.cos_t;
	}
	reflectance = (((comps->n1 - comps->n2) / (comps->n1 + comps->n2)) * \
		((comps->n1 - comps->n2) / (comps->n1 + comps->n2)));
	return (reflectance + (1 - reflectance) * pow((1 - helper.cos_i), 5));
}
