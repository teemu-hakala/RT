/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:27:24 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/20 12:00:26 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_tuple reflect(t_tuple *input, t_tuple *normal)
{
	t_tuple result;
	t_fl temp;

	temp = 2 * dot_product(input, normal);
	*normal = tuple_scale(normal, temp);
	result = (tuple_sub(input, normal));
	return (result);
}

void lighting(t_material *material, t_light *light, t_phong *vectors, t_tuple *point)
{
	t_fl	cos_incidence;
	t_fl	cos_reflect_eye;
	t_fl	factor;


	material->effective_col = tuple_multi(&material->colour, &light->intensity);
	vectors->light_vector = normalize(&(tuple_sub(&light->position, &point)));
	material->amb_col = tuple_scale(&material->effective_col, material->ambient);
	cos_incidence = dot_product(&vectors->light_vector, &vectors->surface_normal);
	if (cos_incidence < 0.0)
	{
		material->diffuse = 0.0; // I assume this means black;
		material->specular = 0.0; //same here;
	}
	else
	{
		material->dif_col = tuple_scale(&(tuple_scale(&material->effective_col, material->diffuse)), cos_incidence);
		vectors->reflection_vector = reflect(&vectors->light_vector, &vectors->surface_normal);
		cos_reflect_eye = dot_product(&vectors->reflection_vector, &vectors->eye_vector);
		if (cos_reflect_eye <= 0.0)
			material->specular = 0.0;
		else
		{
			factor = pow(cos_reflect_eye, material->shininess);
			material->spec_col = tuple_scale(&(tuple_scale(&light->intensity, material->specular)), factor);
		}
	}
	material->colour = tuple_add(&tuple_add(& material->amb_col, &material->dif_col), &material->spec_col);
}