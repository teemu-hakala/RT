#include "RT.h"

t_info get_lighting_info(t_material material, t_appearance appearance, \
	t_transform transform, t_tuple colour)
{
	return ((t_info){
		.material = material,
		.appearance = appearance,
		.transform = transform,
		.col = colour
	});
}

void	lighting_cont(t_info *info, t_light *light, t_phong *vectors,
	t_fl incidence_l)
{
	t_fl		reflect_l;
	t_fl		factor;
	t_material	material;

	material = info->material;
	info->channels.diff = tuple_scale(
			tuple_scale(material.col_mash, material.diffuse), incidence_l);
	vectors->reflection = reflect(
			tuple_scale(vectors->light, -1.0), vectors->surface_normal);
	reflect_l = dot_product(vectors->reflection, vectors->eye);
	if (reflect_l <= 0.0)
		info->channels.spec = vector(0, 0, 0);
	else
	{
		factor = pow(reflect_l, material.shininess);
		info->channels.spec = tuple_scale(
				tuple_scale(light->intensity, material.specular), factor);
	}
}

t_tuple	lighting(t_info *info, t_light *light, t_phong vectors,
	t_tuple point)
{
	t_fl		incidence_l;

	info->material.col_mash = tuple_multi(info->col, \
		light->intensity);
	vectors.light = normalize(tuple_sub(light->position, point));
	info->channels.amb = tuple_scale(info->material.col_mash, \
		info->material.ambient);
	incidence_l = dot_product(vectors.light, vectors.surface_normal);
	if (incidence_l < 0.0)
	{
		info->channels.diff = vector(0, 0, 0);
		info->channels.spec = vector(0, 0, 0);
	}
	else
		lighting_cont(info, light, &vectors, incidence_l);
	if (vectors.in_shadow == true)
		return (info->channels.amb);
	return (tuple_add(
			tuple_add(info->channels.amb, info->channels.diff),
			info->channels.spec));
}
