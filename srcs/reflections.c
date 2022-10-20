/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:27:24 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/20 15:49:56 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_tuple	hit_position(t_ray *ray, t_fl distance)
{
	t_tuple temp;
	temp = tuple_scale(&ray->origin, distance);
	temp = tuple_add(&ray->origin, &temp);

	return (temp);
}

t_tuple	reflect(t_tuple *input, t_tuple *normal)
{
	t_tuple	result;
	t_fl	temp;

	temp = 2 * dot_product(input, normal);
	*normal = tuple_scale(normal, temp);
	result = (tuple_sub(input, normal));
	return (result);
}
/* l stands for angle. we can change that. */

void	lighting_cont(t_material *material, t_pt_light *light, t_phong *vectors,
	t_fl incidence_l)
{
	t_tuple	temp;
	t_fl	reflect_l;
	t_fl	factor;

	temp = tuple_scale(&material->col_mash, material->diffuse);
	material->dif_col = tuple_scale(&temp, incidence_l);
	temp = tuple_scale (&vectors->light, -1.0);
	vectors->reflection = reflect(&temp, &vectors->surface_normal);
	reflect_l = dot_product(&vectors->reflection, &vectors->eye);
	if (reflect_l <= 0.0)
		material->specular = 0.0;
	else
	{
		factor = pow(reflect_l, material->shininess);
		temp = tuple_scale(&light->intensity, material->specular);
		material->spec_col = tuple_scale(&temp, factor);
	}
}

void	lighting(t_material *material, t_pt_light *light, t_phong *vectors,
	t_tuple *point)
{
	t_fl	incidence_l;
	t_tuple	temp;

	material->col_mash = tuple_multi(&material->colour, &light->intensity);
	temp = tuple_sub(&light->position, point);
	vectors->light = normalize(&temp);
	material->amb_col = tuple_scale(&material->col_mash, material->ambient);
	incidence_l = dot_product(&vectors->light, &vectors->surface_normal);
	if (incidence_l < 0.0)
	{
		material->diffuse = 0.0;
		material->specular = 0.0;
	}
	else
		lighting_cont(material, light, vectors, incidence_l);
	temp = tuple_add(& material->amb_col, &material->dif_col);
	material->colour = tuple_add(&temp, &material->spec_col);
}
