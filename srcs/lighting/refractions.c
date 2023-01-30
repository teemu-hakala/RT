








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


t_tuple	refracted_colour(t_world *world, t_hit *hit)
{
	t_fl	transparency;
	t_snell	calc;
	t_tuple	refracted_col;

	transparency = hit->intersection.material.transparency;
	if (transparency < EPSILON && transparency > -EPSILON)
		return (point(0, 0, 0));
	if (world->refraction_lifetime-- <= 0)
		return (point(0, 0, 0));
	calc.n_ratio = hit->computations.n1 / hit->computations.n2;
	calc.cos_i = dot_product(hit->computations.vectors.eye, \
		hit->computations.vectors.surface_normal);
	calc.sin2_t = (calc.n_ratio * calc.n_ratio) * \
		(1 - (calc.cos_i * calc.cos_i));
	if (calc.sin2_t > 1)
	{
		//printf("sin2t = %0.2f\n", calc.sin2_t);
		return (point(0, 0, 0));
	}
	calc.cos_t = sqrt(1 - calc.sin2_t);
	world->refracted_ray.direction = normalize(tuple_sub \
		(tuple_scale(hit->computations.vectors.surface_normal, \
		(calc.n_ratio * calc.cos_i - calc.cos_t)), \
		tuple_scale(hit->computations.vectors.eye, calc.n_ratio)));
	world->refracted_ray.origin = hit->computations.under_point;
	refracted_col = colour_at(world, world->refracted_ray);
	//refracted_col = tuple_multi(refracted_col, hit->intersection.material.init_colour);
	return (tuple_scale(refracted_col, transparency));
}

t_fl	schlick(t_hit *hit)
{
	t_snell	t;
	t_fl	reflectance;

	t.cos_i = dot_product(hit->computations.vectors.eye, \
		hit->computations.vectors.surface_normal);
	if (hit->computations.n1 > hit->computations.n2)
	{
		t.n_ratio = hit->computations.n1 / hit->computations.n2;
		t.sin2_t = (t.n_ratio * t.n_ratio) * (1 - (t.cos_i * t.cos_i));
		if (t.sin2_t >= 1)
			return (1.0);
		t.cos_t = sqrt(1 - t.sin2_t);
		t.cos_i = t.cos_t;
	}
	reflectance = pow(((hit->computations.n1 - \
		hit->computations.n2) / \
			(hit->computations.n1 + hit->computations.n2)), 2);
	return (reflectance + (1 - reflectance) * pow((1 - t.cos_i), 5));
}
