








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

typedef struct s_snell_calculations
{
	t_fl	n_ratio;
	t_fl	cos_i;
	t_fl	sin2_t;
	t_fl	cos_t;
}				t_snell;

int	check_for_total_internal_reflection(t_snell *helper)
{
	if (helper->sin2_t > 1)
		return (true);
	return (false);
}


void	calculate_angles(t_comp *computations, t_snell *helper)
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
	t_fl	transparency;
	t_snell	calc;
	t_comp	comp;

	(void)computations;
	comp = world->hit.computations;
	transparency = world->hit.intersection.material.transparency;
	if (transparency < EPSILON && transparency > -EPSILON)
		return (point(0, 0, 0));
	if (world->refraction_lifetime <= 0)
		return (point(0, 0, 0));
	calc.n_ratio = comp.n1 / comp.n2;
	calc.cos_i = dot_product(comp.vectors.eye, comp.vectors.surface_normal);
	calc.sin2_t = pow(calc.n_ratio, 2) * (1 - pow(calc.cos_i, 2));
	if (calc.sin2_t > 1)
		return (point(0, 0, 0));
	return (point(1, 1, 1));
	calc.cos_t = sqrt(1 - calc.sin2_t);
	world->refracted_ray.direction = tuple_sub(tuple_scale(comp.vectors.surface_normal, \
	(calc.n_ratio * calc.cos_i - calc.cos_t)), tuple_scale(comp.vectors.eye, calc.n_ratio));
}

// t_tuple	refracted_colour(t_world *world, t_comp *computations)
// {
// 	t_tuple	refracted_colour;
// 	t_fl	transparency;
// 	t_tuple	direction;
// 	t_snell	helper;

// 	refracted_colour = point(0, 0, 0);
// 	transparency = world->hit.intersection.material.transparency;
// 	calculate_angles(computations, &helper);
// 	direction = tuple_sub(tuple_scale(computations->vectors.surface_normal, \
// 		(helper.n_ratio * (helper.cos_i - helper.cos_t))), \
// 		tuple_scale(computations->vectors.eye, helper.n_ratio));
// 	if (world->refraction_lifetime-- <= 0)
// 		return (refracted_colour);
// 	if (transparency < EPSILON && transparency > -EPSILON)
// 		return (refracted_colour);
// 	if (check_for_total_internal_reflection(&helper) == true)
// 		return (refracted_colour);
// 	world->refracted_ray = ray(computations->under_point, direction);
// 	refracted_colour = colour_at(world, world->refracted_ray);
// 	return (tuple_scale(refracted_colour, transparency));
// }

t_fl	schlick(t_comp *comps)
{
	t_snell	helper;
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

// t_fl	schlick(t_comp *comps)
// {
// 	t_snell t;
// 	t_fl	reflectance;
// 	t.cos_i = dot_product(comps->vectors.eye, comps->vectors.surface_normal);
// 	if (comps->n1 > comps->n2)
// 	{
// 		t.n_ratio = comps->n1 / comps->n2;
// 		t.sin2_t = pow(t.n_ratio, 2) * (1 - pow(t.cos_i, 2));
// 		if (t.sin2_t > 1)
// 			return (1.0);
// 	}
// 	t.cos_t = sqrt(1 - t.sin2_t);
// 	t.cos_i = t.cos_t;
// 	reflectance = pow(((comps->n1 - comps->n2) / (comps->n1 + comps->n2)), 2);
// 	return (reflectance + (1 - reflectance) * pow((1 - t.cos_i), 5));
// }