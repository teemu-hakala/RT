











#include "RT.h"

t_tuple	reflect(t_tuple input, t_tuple normal)
{
	return (tuple_sub(input,
			tuple_scale(normal, 2 * dot_product(input, normal))));
}

// void	lighting_cont(t_material *material, t_light *light, t_phong *vectors,
// 	t_fl incidence_l)
// {
// 	t_fl	reflect_l;
// 	t_fl	factor;

// 	material->dif_col = tuple_scale(
// 			tuple_scale(material->col_mash, material->diffuse), incidence_l);
// 	vectors->reflection = reflect(
// 			tuple_scale(vectors->light, -1.0), vectors->surface_normal);
// 	reflect_l = dot_product(vectors->reflection, vectors->eye);
// 	if (reflect_l <= 0.0)
// 		material->spec_col = vector(0, 0, 0);
// 	else
// 	{
// 		factor = pow(reflect_l, material->shininess);
// 		material->spec_col = tuple_scale(
// 				tuple_scale(light->intensity, material->specular), factor);
// 	}
// }

// t_tuple	lighting(t_material material, t_light *light, t_phong vectors,
// 	t_tuple point)
// {
// 	t_fl	incidence_l;

// 	material.col_mash = tuple_multi(material.init_colour, light->intensity);
// 	vectors.light = normalize(tuple_sub(light->position, point));
// 	material.amb_col = tuple_scale(material.col_mash, material.ambient);
// 	incidence_l = dot_product(vectors.light, vectors.surface_normal);
// 	if (incidence_l < 0.0)
// 	{
// 		material.dif_col = vector(0, 0, 0);
// 		material.spec_col = vector(0, 0, 0);
// 	}
// 	else
// 		lighting_cont(&material, light, &vectors, incidence_l);
// 	if (vectors.in_shadow == true)
// 		return (material.amb_col);
// 	return (tuple_add(
// 			tuple_add(material.amb_col, material.dif_col), material.spec_col));
// }
// //should move vector results

void	is_shadow(t_world *world, t_tuple point, t_light *light)
{
	t_tuple	temp;
	t_tuple	direction;
	t_fl	distance;
	t_ray	ray;

	temp = tuple_sub(light->position, point);
	distance = magnitude(temp);
	direction = normalize(temp);
	ray = (t_ray){point, direction};
	vec_clear(&world->intersections);
	intersect_world(world, ray);
	identify_hit(world, &world->shadow_hit);
	world->hit.computations.vectors.in_shadow = false;
	if (world->shadow_hit.hit_check == true)
	{
		if (world->shadow_hit.intersection.time < distance)
		{
			world->hit.computations.vectors.in_shadow = true;
		}
	}
}
