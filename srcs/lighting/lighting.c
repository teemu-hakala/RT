/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraivio <jraivio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:21:42 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/12 17:31:49 by jraivio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	lighting_cont(t_hit *hit, t_light *light, t_phong *vectors, \
	t_const *channels)
{
	t_fl		reflect_l;
	t_fl		factor;
	t_material	material;
	t_fl		incidence_l;

	incidence_l = dot_product(vectors->light, vectors->surface_normal);
	material = hit->intersection.material;
	channels->diff = tuple_scale(
			tuple_scale(material.col_mash, material.diffuse), incidence_l);
	vectors->reflection = reflect(
			tuple_scale(vectors->light, -1.0), vectors->surface_normal);
	reflect_l = dot_product(vectors->reflection, vectors->eye);
	if (light->type == LIGHT_PARALLEL || reflect_l <= 0.0 || vectors->in_shadow)
		channels->spec = vector(0, 0, 0);
	else
	{
		factor = pow(reflect_l, material.shininess);
		channels->spec = tuple_scale(
				tuple_scale(light->intensity, material.specular), factor);
	}
}

t_tuple	lighting(t_light *light, t_phong vectors, t_hit *hit)
{
	t_fl		incidence_l;
	t_const		channels;

	hit->intersection.material.col_mash = \
		tuple_multi(hit->intersection.material.init_colour, light->intensity);
	if (light->type == LIGHT_SPOT)
		vectors.light = normalize(tuple_sub(light->position, \
			hit->computations.over_point));
	else
		vectors.light = normalize(light->direction);
	channels.amb = tuple_scale(hit->intersection.material.col_mash, \
		hit->intersection.material.ambient);
	incidence_l = dot_product(vectors.light, vectors.surface_normal);
	if (incidence_l < 0.0)
	{
		channels.diff = vector(0, 0, 0);
		channels.spec = vector(0, 0, 0);
	}
	else
		lighting_cont(hit, light, &vectors, &channels);
	if (vectors.shadow_occlusion >= 1)
		return (channels.amb);
	return (tuple_add(tuple_scale(
				tuple_add(channels.amb, channels.diff), \
				1 - vectors.shadow_occlusion), channels.spec));
}
