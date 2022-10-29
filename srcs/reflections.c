#include "RTv1.h"

t_tuple	hit_position(t_ray *ray, t_fl distance)
{
	return (tuple_add(ray->origin, tuple_scale(ray->direction, distance)));

}

t_tuple	reflect(t_tuple input, t_tuple normal)
{
	return (tuple_sub(input,
			tuple_scale(normal, 2 * dot_product(input, normal))));
}

/* l stands for angle. we can change that. */

void	lighting_cont(t_material *material, t_light *light, t_phong *vectors,
	t_fl incidence_l)
{
	t_fl	reflect_l;
	t_fl	factor;

	material->dif_col = colour_scale(
			colour_scale(material->col_mash, material->diffuse), incidence_l);
	vectors->reflection = reflect(
			tuple_scale(vectors->light, -1.0), vectors->surface_normal);
	reflect_l = dot_product(vectors->reflection, vectors->eye);
	if (reflect_l <= 0.0)
		material->spec_col = colour(1, 0, 0, 0);
	else
	{
		factor = pow(reflect_l, material->shininess);
		material->spec_col = colour_scale(
				colour_scale(light->intensity, material->specular), factor);
	}
}

t_tuple	lighting(t_material material, t_light *light, t_phong vectors,
	t_tuple point)
{
	t_fl	incidence_l;

	material.col_mash = tuple_multi(material.colour, light->intensity);
	vectors.light = normalize(tuple_sub(light->position, point));
	material.amb_col = colour_scale(material.col_mash, material.ambient);
	incidence_l = dot_product(vectors.light, vectors.surface_normal);
	// printf("incidence angle: %f\n", incidence_l);
	if (incidence_l < 0.0)
	{
		material.dif_col = colour(1, 0, 0, 0);
		material.spec_col = colour(1, 0, 0, 0);
	}
	else
		lighting_cont(&material, light, &vectors, incidence_l);
	// printf("ambient col: %f, %f, %f, %f\n", material.amb_col.tuple.units.x, material.amb_col.tuple.units.y, material.amb_col.tuple.units.z, material.amb_col.tuple.units.w);
	// printf("diff col: %f, %f, %f, %f\n", material.dif_col.tuple.units.x, material.dif_col.tuple.units.y, material.dif_col.tuple.units.z, material.dif_col.tuple.units.w);
	// printf("spec col: %f, %f, %f, %f\n", material.spec_col.tuple.units.x, material.spec_col.tuple.units.y, material.spec_col.tuple.units.z, material.spec_col.tuple.units.w);
	return (tuple_add(
			tuple_add(material.amb_col, material.dif_col), material.spec_col));
}
//should move vector results