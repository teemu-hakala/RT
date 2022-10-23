/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 10:18:04 by thakala           #+#    #+#             */
/*   Updated: 2022/10/23 11:06:01 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static t_tuple	default_origin(void)
{
	return (point(0, 0, 0));
}

static t_transform	default_transform_1(void)
{
	t_transform	d;

	d.translation = point(0, 0, 0);
	d.rotation = point(0, 0, 0);
	d.scale = point(1, 1, 1);
	transform_object(&d);
	return (d);
}

static t_transform	default_transform_2(void)
{
	t_transform	d;

	d.translation = point(0, 0, 0);
	d.rotation = point(0, 0, 0);
	d.scale = point(0.5, 0.5, 0.5);
	transform_object(&d);
	return (d);
}

static t_material	default_material_1(void)
{
	return ((t_material){
		.ambient = 0.1,
		.diffuse = 0.9,
		.specular = 0.9,
		.shininess = 200,
		.colour = (t_tuple)
		{
			.tuple.colour = {.a = 0.0, .r = 0.8, .g = 1.0, .b = 0.6}
		}
	});
}

static t_material	default_material_2(void)
{
	return ((t_material){
		.ambient = 0.1,
		.diffuse = 0.9,
		.specular = 0.9,
		.shininess = 200,
		.colour = (t_tuple)
		{
			.tuple.colour = {.a = 0.0, .r = 1.0, .g = 0.2, .b = 1.0}
		}
	});
}

static t_light	default_light(void)
{
	return ((t_light){
		.origin = point(-10, 10, -10),
		.transform = default_transform_1(),
		.intensity = colour(1, 1, 1, 1),
		.ambience = 0.1
	});
}

t_world	default_world(t_win *win)
{
	t_world		world;
	t_object	sphere_1;
	t_object	sphere_2;

	world.objects = (t_objects){.list = \
		(t_object *)malloc(sizeof(t_object) * 2), .count = 2};
	world.lights = (t_lights){.list = \
		(t_light *)malloc(sizeof(t_light) * 1), .count = 1};
	if (world.objects.list == NULL || world.lights.list == NULL)
		handle_errors(win, "one of default_world mallocs returned NULL\n");
	sphere_1 = sphere(default_origin(), default_transform_1(),
			default_material_1());
	sphere_2 = sphere(default_origin(), default_transform_2(),
			default_material_2());
	world.objects.list[0] = sphere_1;
	world.objects.list[1] = sphere_2;
	world.lights.list[0] = default_light();
}
