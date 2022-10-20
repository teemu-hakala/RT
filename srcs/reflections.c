/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:27:24 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/20 10:16:02 by deelliot         ###   ########.fr       */
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

void lighting(t_material *material, t_pt_light *light, t_phong *vectors, t_tuple *point)
{
	t_tuple	colour;
	t_tuple ambient;

	colour = tuple_multi(&material->colour, &light->intensity);
	vectors->light_vector = normalize(&(tuple_sub(&light->position, &point)));
	ambient = tuple_scale(&colour, material->ambient);

}