#include "RT.h"

void	lighting_cont(t_world *world, t_light *light, t_phong *vectors,
	t_fl incidence_l, t_const *channels)
{
	t_fl		reflect_l;
	t_fl		factor;
	t_material	material;

	material = world->hit.intersection.material;
	channels->diff = tuple_scale(
			tuple_scale(material.col_mash, material.diffuse), incidence_l);
	vectors->reflection = reflect(
			tuple_scale(vectors->light, -1.0), vectors->surface_normal);
	reflect_l = dot_product(vectors->reflection, vectors->eye);
	if (light->type == LIGHT_PARALLEL || reflect_l <= 0.0)
		channels->spec = vector(0, 0, 0);
	else
	{
		factor = pow(reflect_l, material.shininess);
		channels->spec = tuple_scale(
				tuple_scale(light->intensity, material.specular), factor);
	}
}

t_tuple	lighting(t_world *world, t_light *light, t_phong vectors,
	t_tuple point)
{
	t_fl		incidence_l;
	t_const		channels;

	world->hit.intersection.material.col_mash = \
		tuple_multi(world->hit.intersection.material.init_colour, \
		light->intensity);
	if (light->type == LIGHT_SPOT)
		vectors.light = normalize(tuple_sub(light->position, point));
	else
		vectors.light = normalize(light->direction);
		channels.amb = tuple_scale(world->hit.intersection.material.col_mash, \
		world->hit.intersection.material.ambient);
	incidence_l = dot_product(vectors.light, vectors.surface_normal);
	if (incidence_l < 0.0)
	{
		channels.diff = vector(0, 0, 0);
		channels.spec = vector(0, 0, 0);
	}
	else
		lighting_cont(world, light, &vectors, incidence_l, &channels);
	if (vectors.in_shadow == true)
		return (channels.amb);
	return (tuple_add(
			tuple_add(channels.amb, channels.diff),
			channels.spec));
}
