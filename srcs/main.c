/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:02:35 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/24 14:38:19 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RTv1.h"

void test_new_ray(void)
{
	t_ray	ray;
	t_tuple	transform;
	t_ray	new;

	ray.origin.tuple.units = (t_units){1.0, 2.0, 3.0, 1.0};
	ray.direction.tuple.units = (t_units){0.0, 1.0, 0.0, 0.0};
	transform.tuple.units = (t_units){3.0, 4.0, 5.0, 1.0};
	new = ray_translation(ray, transform);
	printf("translated: \norigin: {%f, %f, %f}\ndirection: {%f, %f, %f}\n", new.origin.tuple.units.x, new.origin.tuple.units.y, new.origin.tuple.units.z, new.direction.tuple.units.x, new.direction.tuple.units.y, new.direction.tuple.units.z);
	new = ray_scale(ray, transform);
	printf("translated: \norigin: {%f, %f, %f}\ndirection: {%f, %f, %f}\n", new.origin.tuple.units.x, new.origin.tuple.units.y, new.origin.tuple.units.z, new.direction.tuple.units.x, new.direction.tuple.units.y, new.direction.tuple.units.z);
}


void	ft_print_mtx(t_mtx *mtx)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%.1f, ", mtx->array[4 * i + j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	test_matrix_inversion(void)
{
	t_mtx	mtx;
	t_mtx	transformation;

	mtx.tuple_rows[0] = (t_quad_tuple){1.0, 2.0, 1.0, 1.0};
	mtx.tuple_rows[1] = (t_quad_tuple){0.0, 1.0, 0.0, 1.0};
	mtx.tuple_rows[2] = (t_quad_tuple){2.0, 3.0, 4.0, 1.0};
	mtx.tuple_rows[3] = (t_quad_tuple){1.0, 1.0, 1.0, 1.0};

	transformation.tuple_rows[0] = (t_quad_tuple){2.0, 5.0, 1.0, 1.0};
	transformation.tuple_rows[1] = (t_quad_tuple){6.0, 7.0, 1.0, 1.0};
	transformation.tuple_rows[2] = (t_quad_tuple){1.0, 8.0, 1.0, 1.0};
	transformation.tuple_rows[3] = (t_quad_tuple){1.0, 1.0, 1.0, 1.0};

	printf("ORIGINAL mtx:\n");
	ft_print_mtx (&mtx);
	// printf("\nTRANSFORMED mtx\n");
	// matrix_multi_square (&mtx, &transformation, 4);
	// ft_print_mtx (&mtx);
	printf("\nINVERTED mtx\n");
	matrix_inversion (&mtx, 4);
	ft_print_mtx (&mtx);
	printf("\nRE-INVERTED, ORIGINAL, mtx\n");
	matrix_inversion (&mtx, 4);
	ft_print_mtx (&mtx);
}

// void	test_red_disc(void)
// {
// 	t_object	object_sphere;
// 	t_tuple		red;
// 	t_transform	transform;
// 	t_win		win;

// 	transform = (t_transform)
// 	{
// 		.translation = (t_tuple)
// 		{
// 			.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1 }
// 		},
// 		.rotation = (t_tuple)
// 		{
// 			.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1 }
// 		},
// 		.scale = (t_tuple)
// 		{
// 			.tuple.units = (t_units){ 1.0, 1.0, 1.0, POINT_1 }
// 		}
// 	};
// 	red = hex_to_argb(0xFF0000);
// 	object_sphere = sphere(
// 			&(t_tuple){.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1}},
// 			&transform,
// 			&red
// 		);
// 	initialise_window(&win);
// 	plot_points(&win, &object_sphere);
// 	mlx_hook(win.win, KEY_DOWN, 0, handle_input, &win);
// 	mlx_loop(win.mlx);
// }

void	test_normal_at_sphere(void)
{
	t_objects	objects;
	t_object	object_sphere;
	t_transform	transform;
	t_tuple		red;
	t_tuple		point_at;
	t_tuple		normal_at;

	transform = (t_transform)
	{
		.translation = (t_tuple)
		{
			.tuple.units = (t_units){ 0.0, 1.0, 0.0, POINT_1 }
		},
		.rotation = (t_tuple)
		{
			.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1 }
		},
		.scale = (t_tuple)
		{
			.tuple.units = (t_units){ 1.0, 1.0, 1.0, POINT_1 }
		}
	};
	red = hex_to_argb(0xFF0000);
	object_sphere = sphere(
			(t_tuple){.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1}},
			transform,
			(t_material){
				.diffuse = 0.9,
				.specular = 0.9,
				.ambient = 0.1,
				.shininess = 200.0,
				.col_mash = point(0, 0, 0),
				.dif_col = point(0, 0, 0),
				.amb_col = point(0, 0, 0),
				.spec_col = point(0, 0, 0)
			}
		);
	objects.list = (t_object *)malloc(sizeof(t_object) * 10);
	if (objects.list == NULL)
		exit(EXIT_FAILURE);
	objects.list[0] = object_sphere;
	objects.count = 1;
	// translate(&object_sphere.object.sphere.transform.matrix, &object_sphere.object.sphere.transform.translation);
	// scale(&object_sphere.object.sphere.transform.matrix, &object_sphere.object.sphere.transform.scale);
	// object_sphere.object.sphere.transform.inverse = object_sphere.object.sphere.transform.matrix;
	// matrix_inversion(&object_sphere.object.sphere.transform.inverse, 4);
	transform_objects(&objects);
	printf("transformation matrix:\n");
	ft_print_mtx(&objects.list[0].object.sphere.transform.matrix);
	printf("\n\n");
	printf("inverse matrix:\n");
	ft_print_mtx(&objects.list[0].object.sphere.transform.inverse);
	printf("\n\n");
	point_at.tuple.units = (t_units){ 0.0, 1.70711, -0.70711, POINT_1 };
	printf("point: %f, %f, %f, %f\n\n", point_at.tuple.units.x, point_at.tuple.units.y, point_at.tuple.units.z, point_at.tuple.units.w);
	normal_at = normal_at_sphere(&objects.list[0], &point_at);
	printf("normal at point: %f, %f, %f, %f\n\n", normal_at.tuple.units.x, normal_at.tuple.units.y, normal_at.tuple.units.z, normal_at.tuple.units.w);
	free(objects.list);
}

void	test_reflect()
{
	t_tuple input;
	t_tuple normal;
	t_tuple results;

	input.tuple.units = (t_units){1.0, -1.0, 0.0, 0.0};
	normal.tuple.units = (t_units){0, 1, 0, 0};
	results = reflect(input, normal);
	printf("result = %f, %f, %f, %f\n", results.tuple.units.x, results.tuple.units.y, results.tuple.units.z, results.tuple.units.w);
}

void	test_lighting_angled()
{
	t_material	material;
	t_pt_light	light;
	t_phong		vectors;
	t_tuple		point;
	t_tuple		red;
	t_tuple		result_colour;

	red = hex_to_argb(COLOUR_WHITE);

	material.ambient = 0.1;
	material.diffuse = 0.9;
	material.specular = 0.9;
	material.shininess = 200;
	material.colour = red;

	light.intensity.tuple.colour = (t_colour){ 1.0, 1.0, 1.0, 1.0 };
	light.position.tuple.units = (t_units){ 0.0, 10.0, -10.0, POINT_1 };

	vectors.eye.tuple.units = (t_units){ 0.0, -0.7071, -0.7071, VECTOR_0 };
	vectors.surface_normal.tuple.units = (t_units){ 0.0, 0.0, -1.0, VECTOR_0 };

	point.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1 };
	result_colour = lighting(material, light, vectors, point);
	printf("col: %.4f, %.4f, %.4f, %.4f\n", result_colour.tuple.colour.a, \
	result_colour.tuple.colour.r, result_colour.tuple.colour.g, \
	result_colour.tuple.colour.b);
}

void	test_lighting_ambient()
{
	t_material	material;
	t_pt_light	light;
	t_phong		vectors;
	t_tuple		point;
	t_tuple		red;
	t_tuple		result_colour;

	red = hex_to_argb(COLOUR_WHITE);

	material.ambient = 0.1;
	material.diffuse = 0.9;
	material.specular = 0.9;
	material.shininess = 200;
	material.colour = red;

	light.intensity.tuple.units = (t_units){ 1.0, 1.0, 1.0, 1.0 };
	light.position.tuple.units = (t_units){ 0.0, 10.0, 0.0, POINT_1 };

	vectors.eye.tuple.units = (t_units){ 0.0, 0.0, -1.0, VECTOR_0 };
	vectors.surface_normal.tuple.units = (t_units){ 0.0, 0.0, -1.0, VECTOR_0 };

	point.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1 };
	result_colour = lighting(material, light, vectors, point);
	printf("col: %.4f, %.4f, %.4f, %.4f\n", result_colour.tuple.colour.a, \
	result_colour.tuple.colour.r, result_colour.tuple.colour.g, \
	result_colour.tuple.colour.b);
}

void	test_3D_sphere(void)
{
	t_object	object_sphere;
	t_transform	transform;
	t_win		win;
	t_pt_light	light_source;

	transform = (t_transform)
	{
		.translation = point(0, 0, 0),
		.rotation = point(0, 0, 0),
		.scale = point(0.25, 0.25, 0.25)
	};
	transform_object(&transform);
	object_sphere = sphere(
			point(0, 0, 0),
			transform,
			(t_material)
			{
				.colour = colour(0.0, 1.0, 0.2, 1.0),
				.ambient = 0.1,
				.diffuse = 0.9,
				.specular = 0.9,
				.shininess = 200.0,
				.col_mash = vector(0, 0, 0),
				.amb_col = vector(0, 0, 0),
				.dif_col = vector(0, 0, 0),
				.spec_col = vector(0, 0, 0)
			}
		);
	light_source.intensity.tuple.units = (t_units){ 0.0, 1.0, 1.0, 1.0 };
	light_source.position.tuple.units = (t_units){ -10.0, 10.0, -10.0, POINT_1 };

	initialise_window(&win);
	plot_points(&win, &object_sphere, light_source);
	mlx_hook(win.win, KEY_DOWN, 0, handle_input, &win);
	mlx_loop(win.mlx);
}

void	test_3D_sphere_transformed(void)
{
	t_material	material;
	t_transform	transform;
	t_win		win;
	t_pt_light	light_source;

	win.world.objects = (t_objects){.list = (t_object *)malloc(sizeof(t_object) * 1), .count = 1};
	if (win.world.objects.list == NULL)
		handle_errors("test_3d_sphere_transformed win.world.objects.list malloc failed");
	transform = (t_transform)
	{
		.translation = point(0.0, 0.0, 0.0),
		.rotation = point(0.0, 0.0, 0.0),
		.scale = point(0.5, 0.5, 1.0)
	};
	material = (t_material)
	{
		.colour = (t_tuple){.tuple.colour = {0.0, 1.0, 0.2, 1.0}},
		.ambient = 0.1,
		.diffuse = 0.9,
		.specular = 0.9,
		.shininess = 200.0,
		.col_mash = point(0, 0, 0),
		.amb_col = point(0, 0, 0),
		.dif_col = point(0, 0, 0),
		.spec_col = point(0, 0, 0)
	};
	win.world.objects.list[0] = sphere(
			point(0, 0, 0),
			transform,
			material
		);
	transform_objects(&win.world.objects);
	light_source.intensity.tuple.units = (t_units){ 0.0, 1.0, 1.0, 1.0 };
	light_source.position.tuple.units = (t_units){ -10.0, 10.0, -10.0, POINT_1 };

	initialise_window(&win);
	plot_points(&win, &win.world.objects.list[0], light_source);
	mlx_hook(win.win, KEY_DOWN, 0, handle_input, &win);
	mlx_loop(win.mlx);
}

void	test_3D_sphere_params(void)
{
	t_win		win;

	win.world.objects = (t_objects){.list = \
		(t_object *)malloc(sizeof(t_object) * 10), .count = 1};
	if (win.world.objects.list == NULL)
		handle_errors("win.world.objects.list malloc returned NULL");
	win.world.lights = (t_lights){.list = \
		(t_light *)malloc(sizeof(t_light) * 1), .count = 1};
	if (win.world.lights.list == NULL)
		handle_errors("win.world.lights.list malloc returned NULL");
	win.world.camera = (t_camera)
	{
		.origin = point(0.0, 0.0, -5.0),
		.transform = (t_transform) \
		{\
			.translation = point(0.0, 0.0, 0.0), \
			.rotation = point(0.0, 0.0, 0.0), \
			.scale = point(1.0, 1.0, 1.0) \
		},
		.center_of_interest = point(0.0, 0.0, 0.0),
		.field_of_view = (t_fov2){.vertical = M_PI / 3, \
			.horizontal = (t_fl)M_PI / 3 * WIDTH / HEIGHT}
	};
	win.world.objects.list[0] = sphere
	(
		(t_tuple){.tuple.units = (t_units){0.0, 0.0, 0.0, POINT_1}},
		(t_transform)
		{
			.translation = point(0.0, 0.0, 0.0),
			.rotation = point(0.0, 0.0, 0.0),
			.scale = point(1.0, 1.0, 1.0)
		},
		(t_material)
		{
			.colour = (t_tuple){.tuple.colour = {0.0, 0.2, 1.0, 1.0}},
			.ambient = 0.1,
			.diffuse = 0.9,
			.specular = 0.9,
			.shininess = 200.0,
			.col_mash = point(0, 0, 0),
			.amb_col = point(0, 0, 0),
			.dif_col = point(0, 0, 0),
			.spec_col = point(0, 0, 0)
		}
	);
	win.world.lights.list[0] = (t_light)
	{
		.intensity = colour(0.0, 1.0, 1.0, 1.0),
		.origin = point(-10.0, 10.0, -10.0)
	};
	initialise_window(&win);
	plot_points_params(&win);
	mlx_hook(win.win, KEY_DOWN, 0, handle_input, &win);
	mlx_loop(win.mlx);
}

int	main(void)
{
	//test_matrix_inversion();
	// test_red_disc();
	// test_normal_at_sphere();
	// test_reflect();
	test_lighting_angled();
	test_lighting_ambient();
	//test_3D_sphere();
	//test_3D_sphere_transformed();
	test_3D_sphere_params();
	return (0);
}

int	main(int argc, char **argv)
{
	t_win	win;

	if (argc != 2)
		handle_errors(USAGE);
	initialise_world(&win.world);
	parse(&win);
	initialise_window(&win);
	draw();
	mlx_hook(win.win, KEY_DOWN, 0, handle_input, &win);
	mlx_loop(win.mlx);
	return (0);
}
