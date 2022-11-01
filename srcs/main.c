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
	printf("------------------------------------------\n");
	while (i < 4)
	{
		j = 0;
		printf("|");
		while (j < 4)
		{
			printf("% .5f, ", mtx->array[4 * i + j]);
			j++;
		}
		printf("|\n");
		i++;
	}
	printf("------------------------------------------\n");
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

// void	test_normal_at_sphere(void)
// {
// 	t_objects	objects;
// 	t_object	object_sphere;
// 	t_transform	transform;
// 	t_tuple		red;
// 	t_tuple		point_at;
// 	t_tuple		normal_at;

// 	transform = (t_transform)
// 	{
// 		.translation = (t_tuple)
// 		{
// 			.tuple.units = (t_units){ 0.0, 1.0, 0.0, POINT_1 }
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
// 			(t_tuple){.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1}},
// 			transform,
// 			(t_material){
// 				.diffuse = 0.9,
// 				.specular = 0.9,
// 				.ambient = 0.1,
// 				.shininess = 200.0,
// 				.col_mash = point(0, 0, 0),
// 				.dif_col = point(0, 0, 0),
// 				.amb_col = point(0, 0, 0),
// 				.spec_col = point(0, 0, 0)
// 			}
// 		);
// 	objects.list = (t_object *)malloc(sizeof(t_object) * 10);
// 	if (objects.list == NULL)
// 		exit(EXIT_FAILURE);
// 	objects.list[0] = object_sphere;
// 	objects.count = 1;
// 	// translate(&object_sphere.object.sphere.transform.matrix, &object_sphere.object.sphere.transform.translation);
// 	// scale(&object_sphere.object.sphere.transform.matrix, &object_sphere.object.sphere.transform.scale);
// 	// object_sphere.object.sphere.transform.inverse = object_sphere.object.sphere.transform.matrix;
// 	// matrix_inversion(&object_sphere.object.sphere.transform.inverse, 4);
// 	transform_objects(&objects);
// 	printf("transformation matrix:\n");
// 	ft_print_mtx(&objects.list[0].object.sphere.transform.matrix);
// 	printf("\n\n");
// 	printf("inverse matrix:\n");
// 	ft_print_mtx(&objects.list[0].object.sphere.transform.inverse);
// 	printf("\n\n");
// 	point_at.tuple.units = (t_units){ 0.0, 1.70711, -0.70711, POINT_1 };
// 	printf("point: %f, %f, %f, %f\n\n", point_at.tuple.units.x, point_at.tuple.units.y, point_at.tuple.units.z, point_at.tuple.units.w);
// 	normal_at = normal_at_sphere(&objects.list[0], &point_at);
// 	printf("normal at point: %f, %f, %f, %f\n\n", normal_at.tuple.units.x, normal_at.tuple.units.y, normal_at.tuple.units.z, normal_at.tuple.units.w);
// 	free(objects.list);
// }

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
	t_light	light;
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
	result_colour = lighting(material, &light, vectors, point);
	printf("col: %.4f, %.4f, %.4f, %.4f\n", result_colour.tuple.colour.a, \
	result_colour.tuple.colour.r, result_colour.tuple.colour.g, \
	result_colour.tuple.colour.b);
}

void	test_lighting_ambient()
{
	t_material	material;
	t_light	light;
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
	result_colour = lighting(material, &light, vectors, point);
	printf("col: %.4f, %.4f, %.4f, %.4f\n", result_colour.tuple.colour.a, \
	result_colour.tuple.colour.r, result_colour.tuple.colour.g, \
	result_colour.tuple.colour.b);
}
/*
void	test_3D_sphere(void)
{
	t_object	object_sphere;
	t_transform	transform;
	t_win		win;
	t_light	light_source;

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
	plot_points(&win);
	mlx_hook(win.win, KEY_DOWN, 0, handle_input, &win);
	mlx_loop(win.mlx);
}
*/
// void	test_3D_sphere_transformed(void)
// {
// 	t_material	material;
// 	t_transform	transform;
// 	t_win		win;
// 	t_pt_light	light_source;

// 	win.world.objects = (t_objects){.list = (t_object *)malloc(sizeof(t_object) * 1), .count = 1};
// 	if (win.world.objects.list == NULL)
// 		handle_errors("test_3d_sphere_transformed win.world.objects.list malloc failed");
// 	transform = (t_transform)
// 	{
// 		.translation = point(0.0, 0.0, 0.0),
// 		.rotation = point(0.0, 0.0, 0.0),
// 		.scale = point(0.5, 0.5, 1.0)
// 	};
// 	material = (t_material)
// 	{
// 		.colour = (t_tuple){.tuple.colour = {0.0, 1.0, 0.2, 1.0}},
// 		.ambient = 0.1,
// 		.diffuse = 0.9,
// 		.specular = 0.9,
// 		.shininess = 200.0,
// 		.col_mash = point(0, 0, 0),
// 		.amb_col = point(0, 0, 0),
// 		.dif_col = point(0, 0, 0),
// 		.spec_col = point(0, 0, 0)
// 	};
// 	win.world.objects.list[0] = sphere(
// 			point(0, 0, 0),
// 			transform,
// 			material
// 		);
// 	transform_objects(&win.world.objects);
// 	light_source.intensity.tuple.units = (t_units){ 0.0, 1.0, 1.0, 1.0 };
// 	light_source.position.tuple.units = (t_units){ -10.0, 10.0, -10.0, POINT_1 };

// 	initialise_window(&win);
// 	plot_points(&win, &win.world.objects.list[0], light_source);
// 	mlx_hook(win.win, KEY_DOWN, 0, handle_input, &win);
// 	mlx_loop(win.mlx);
// }

// void	test_3D_sphere_params(void)
// {
// 	t_win		win;

// 	win.world.objects = (t_objects){.list = \
// 		(t_object *)malloc(sizeof(t_object) * 10), .count = 1};
// 	if (win.world.objects.list == NULL)
// 		handle_errors("win.world.objects.list malloc returned NULL");
// 	win.world.lights = (t_lights){.list = \
// 		(t_light *)malloc(sizeof(t_light) * 1), .count = 1};
// 	if (win.world.lights.list == NULL)
// 		handle_errors("win.world.lights.list malloc returned NULL");
// 	win.world.camera = (t_camera)
// 	{
// 		.origin = point(0.0, 0.0, -5.0),
// 		.transform = (t_transform) \
// 		{\
// 			.translation = point(0.0, 0.0, 0.0), \
// 			.rotation = point(0.0, 0.0, 0.0), \
// 			.scale = point(1.0, 1.0, 1.0) \
// 		},
// 		.center_of_interest = point(0.0, 0.0, 0.0),
// 		.field_of_view = (t_fov2){.vertical = M_PI / 3, \
// 			.horizontal = (t_fl)M_PI / 3 * WIDTH / HEIGHT}
// 	};
// 	win.world.objects.list[0] = sphere
// 	(
// 		(t_tuple){.tuple.units = (t_units){0.0, 0.0, 0.0, POINT_1}},
// 		(t_transform)
// 		{
// 			.translation = point(0.0, 0.0, 0.0),
// 			.rotation = point(0.0, 0.0, 0.0),
// 			.scale = point(1.0, 1.0, 1.0)
// 		},
// 		(t_material)
// 		{
// 			.colour = (t_tuple){.tuple.colour = {0.0, 0.2, 1.0, 1.0}},
// 			.ambient = 0.1,
// 			.diffuse = 0.9,
// 			.specular = 0.9,
// 			.shininess = 200.0,
// 			.col_mash = point(0, 0, 0),
// 			.amb_col = point(0, 0, 0),
// 			.dif_col = point(0, 0, 0),
// 			.spec_col = point(0, 0, 0)
// 		}
// 	);
// 	win.world.lights.list[0] = (t_light)
// 	{
// 		.intensity = colour(0.0, 1.0, 1.0, 1.0),
// 		.origin = point(-10.0, 10.0, -10.0)
// 	};
// 	initialise_window(&win);
// 	plot_points_params(&win);
// 	mlx_hook(win.win, KEY_DOWN, 0, handle_input, &win);
// 	mlx_loop(win.mlx);
// }

void	test_view_transform_default()
{
	t_mtx	mtx;
	t_tuple	from;
	t_tuple	to;
	t_tuple	up;

	from = point(0, 0, 0);
	to = point(0, 0, -1);
	up = vector(0, 1, 0);
	mtx = view_transform(from, to, up);
	ft_print_mtx(&mtx);
}

void	test_view_transform_positive_z()
{
	t_mtx	mtx;
	t_tuple	from;
	t_tuple	to;
	t_tuple	up;

	from = point(0, 0, 0);
	to = point(0, 0, 1);
	up = vector(0, 1, 0);
	mtx = view_transform(from, to, up);
	ft_print_mtx(&mtx);
}

void	test_view_transform_moves_the_world()
{
	t_mtx	mtx;
	t_tuple	from;
	t_tuple	to;
	t_tuple	up;

	from = point(0, 0, 8);
	to = point(0, 0, 0);
	up = vector(0, 1, 0);
	mtx = view_transform(from, to, up);
	ft_print_mtx(&mtx);
}

void	test_view_transform_arbitrary()
{
	t_mtx	mtx;
	t_tuple	from;
	t_tuple	to;
	t_tuple	up;

	from = point(1, 3, 2);
	to = point(4, -2, 8);
	up = vector(1, 1, 0);
	mtx = view_transform(from, to, up);
	ft_print_mtx(&mtx);
}

void	test_view_transform(void)
{
	test_view_transform_default();
	test_view_transform_positive_z();
	test_view_transform_moves_the_world();
	test_view_transform_arbitrary();
}

void	print_indented(uint8_t indent_level, const char *string)
{
	uint8_t	uc;

	uc = 0;
	while (uc < indent_level)
	{
		printf("\t");
		uc++;
	}
	printf("%s", string);
}

void	print_matrix(t_mtx *mtx, uint8_t indent_level, const char *description)
{
	char	*str;
	uint8_t	i;
	uint8_t	j;

	i = 0;
	asprintf(&str, "%s (%s)\n", "MATRIX ", description);
	print_indented(indent_level, str);
	free(str);
	print_indented(indent_level, "{\n");
	print_indented(indent_level + 1, "------------------------------------------\n");
	while (i < 4)
	{
		j = 0;
		print_indented(indent_level + 1, "|");
		while (j < 4)
		{
			printf("% .5f, ", mtx->array[4 * i + j]);
			j++;
		}
		printf("|\n");
		i++;
	}
	print_indented(indent_level + 1, "------------------------------------------\n");
	print_indented(indent_level, "}\n");
}


void	print_tuple(t_tuple *tuple, uint8_t indent_level, const char *description)
{
	char	*str;

	asprintf(&str, "%s (%s)\n", "TUPLE ", description);
	print_indented(indent_level, str);
	free(str);
	print_indented(indent_level, "{\n");
	asprintf(&str, "(% .5lf, % .5lf, % .5lf, % .5lf)\n", tuple->array[X], tuple->array[Y], \
		tuple->array[Z], tuple->array[W]);
	print_indented(indent_level + 1, str);
	free(str);
	print_indented(indent_level, "}\n");
}

void	print_transform(t_transform *transform, uint8_t indent_level, const char *description)
{
	char	*str;

	asprintf(&str, "%s (%s)\n", "TRANSFORM ", description);
	print_indented(indent_level, str);
	free(str);
	print_indented(indent_level, "{\n");
	print_matrix(&transform->matrix, indent_level + 1, "transform->matrix");
	print_matrix(&transform->inverse, indent_level + 1, "transform->inverse");
	print_tuple(&transform->translation, indent_level + 1, "transform->translation");
	print_tuple(&transform->rotation, indent_level + 1, "transform->rotation");
	print_tuple(&transform->scale, indent_level + 1, "transform->scale");
	print_indented(indent_level, "}\n");
}

void	print_camera(t_camera *camera, uint8_t indent_level)
{
	char	*str;

	print_indented(indent_level, "CAMERA\n");
	print_indented(indent_level, "{\n");
	asprintf(&str, "camera->size.horizontal %hu\n", camera->size.horizontal);
	print_indented(indent_level + 1, str);
	free(str);
	asprintf(&str, "camera->size.vertical %hu\n", camera->size.vertical);
	print_indented(indent_level + 1, str);
	free(str);
	asprintf(&str, "camera->field_of_view %lf\n", camera->field_of_view);
	print_indented(indent_level + 1, str);
	free(str);
	print_tuple(&camera->origin, indent_level + 1, "camera->origin");
	print_transform(&camera->transform, indent_level + 1, "camera->transform");
	asprintf(&str, "camera->pixel_size %lf\n", camera->pixel_size);
	print_indented(indent_level + 1, str);
	free(str);
	print_indented(indent_level, "}\n");
}

void	print_ray(t_ray *ray, uint8_t indent_level)
{
	print_indented(indent_level, "RAY\n");
	print_indented(indent_level, "{\n");
	print_tuple(&ray->origin, indent_level + 1, "ray->origin");
	print_tuple(&ray->direction, indent_level + 1, "ray->direction");
	print_indented(indent_level, "}\n");
}

void test_camera_construction(void)
{
	t_camera	cam;

	cam = camera(camera_origin(), camera_transform(), (t_fl)M_PI_2, (t_canvas){.vertical = 120, .horizontal = 160});
	print_camera(&cam, 0);
}

void test_camera_pixel_size_horizontal_canvas(void)
{
	t_camera	cam;

	cam = camera(camera_origin(), camera_transform(), (t_fl)M_PI_2, (t_canvas){.vertical = 125, .horizontal = 200});
	print_camera(&cam, 0);
}

void test_camera_pixel_size_vertical_canvas(void)
{
	t_camera	cam;

	cam = camera(camera_origin(), camera_transform(), (t_fl)M_PI_2, (t_canvas){.vertical = 125, .horizontal = 200});
	print_camera(&cam, 0);
}

void test_camera_ray_centre_of_canvas(void)
{
	t_camera	cam;
	t_ray		ray;

	cam = camera(camera_origin(), camera_transform(), (t_fl)M_PI_2, (t_canvas){.vertical = 101, .horizontal = 201});
	print_camera(&cam, 0);
	ray = ray_for_pixel(&cam, (t_canvas){.vertical = 50, .horizontal = 100});
	print_ray(&ray, 0);
}

void test_camera_ray_corner_of_canvas(void)
{
	t_camera	cam;
	t_ray		ray;

	cam = camera(camera_origin(), camera_transform(), (t_fl)M_PI_2, (t_canvas){.vertical = 101, .horizontal = 201});
	print_camera(&cam, 0);
	ray = ray_for_pixel(&cam, (t_canvas){.vertical = 0, .horizontal = 0});
	print_ray(&ray, 0);
}

void test_camera_ray_transformed(void)
{
	t_camera	cam;
	t_ray		ray;

	cam = camera(camera_origin(), camera_transform(), (t_fl)M_PI_2, (t_canvas){.vertical = 101, .horizontal = 201});
	rotate(&cam.transform.matrix, &(t_tuple){.tuple.rotation.y_hei_vert_yaw = M_PI_4});
	translate(&cam.transform.matrix, &(t_tuple){.tuple.units = {.x = 0, .y = -2, .z = 5, .w = POINT_1}});
	cam.transform.inverse = cam.transform.matrix;
	matrix_inversion(&cam.transform.inverse, 4);
	print_camera(&cam, 0);
	ray = ray_for_pixel(&cam, (t_canvas){.vertical = 50, .horizontal = 100});
	print_ray(&ray, 0);
}

void	test_camera(void)
{
	test_camera_construction();
	test_camera_pixel_size_horizontal_canvas();
	test_camera_pixel_size_vertical_canvas();
	test_camera_ray_centre_of_canvas();
	test_camera_ray_corner_of_canvas();
	test_camera_ray_transformed();
}


static void	vec_print(void *data_point)
{
	t_intersect	*xs;

	xs = (t_intersect *)data_point;
	printf("time %lf\n", xs->time);
}

void	test_colour_at(t_win *win)
{
	t_camera cam;
	cam = camera(camera_origin(), camera_transform(), (t_fl)M_PI_2, (t_canvas){.vertical = 101, .horizontal = 201});
	win->world.ray = ray_for_pixel(&cam, (t_canvas){.vertical = 50, .horizontal = 100});
	default_world(&win->world);
	colour_at(&win->world);
	vec_iter(&win->world.intersections, vec_print);
	//printf(world->hit);
}

void	print_material(t_material *material, uint8_t indent_level, const char *description)
{
	char	*str;

	asprintf(&str, "%s (%s)\n", "MATERIAL ", description);
	print_indented(indent_level, str);
	free(str);
	print_indented(indent_level, "{\n");
	print_tuple(
		&(t_tuple)
		{
			.tuple.units = {
				.x = material->ambient,
				.y = material->diffuse,
				.z = material->specular,
				.w = material->shininess
			}
		}, indent_level + 1,
		"ambient, diffuse, specular, shininess"
	);
	print_tuple(&material->colour, indent_level + 1,"object->initial_colour");
	print_indented(indent_level, "}\n");
}

void	print_phong(t_phong *phong, uint8_t indent_level, const char *description)
{
	char	*str;

	asprintf(&str, "%s (%s)\n", "PHONG ", description);
	print_indented(indent_level, str);
	free(str);
	print_indented(indent_level, "{\n");
	print_tuple(&phong->eye, indent_level + 1, "phong->eye");
	print_tuple(&phong->light, indent_level + 1, "phong->light");
	print_tuple(&phong->surface_normal, indent_level + 1, "phong->surface_normal");
	print_tuple(&phong->reflection, indent_level + 1, "phong->reflection");
	print_indented(indent_level, "}\n");
}

void	print_computations(t_comp *computations, uint8_t indent_level, const char *description)
{
	char	*str;

	asprintf(&str, "%s (%s)\n", "COMPUTATIONS ", description);
	print_indented(indent_level, str);
	free(str);
	print_indented(indent_level, "{\n");
	asprintf(&str, "computations->time % .5lf\n", computations->time);
	print_indented(indent_level + 1, str);
	free(str);
	asprintf(&str, "e_object_type: %d\n", computations->type);
	print_indented(indent_level + 1, str);
	free(str);
	print_tuple(&computations->point, indent_level + 1, "computations->point");
	print_phong(&computations->vectors, indent_level + 1, "computations->vectors");
	print_indented(indent_level, "}\n");
}

void	print_light(t_light *light, uint8_t indent_level, uint64_t object_index)
{
	char	*str;

	asprintf(&str, "%s #%04llu\n", "LIGHT ", object_index);
	print_indented(indent_level, str);
	free(str);
	print_indented(indent_level, "{\n");
	print_tuple(&light->position, indent_level + 1, "light->position");
	print_tuple(&light->intensity, indent_level + 1, "light->intensity");
	print_transform(&light->transform, indent_level + 1, "light->transform");
	print_indented(indent_level, "}\n");
}

typedef void	(*t_print_object)(t_object *, uint8_t, uint64_t);

void	print_plane(t_object *plane, uint8_t indent_level, uint64_t object_index)
{
	(void)plane;
	(void)indent_level;
	(void)object_index;
}

void	print_sphere(t_object *sphere, uint8_t indent_level, uint64_t object_index)
{
	char	*str;

	asprintf(&str, "%s #%04llu\n", "SPHERE ", object_index);
	print_indented(indent_level, str);
	free(str);
	print_indented(indent_level, "{\n");
	print_tuple(&sphere->object.sphere.origin, indent_level + 1, "sphere->object.sphere.origin");
	print_transform(&sphere->object.sphere.transform, indent_level + 1, "sphere->object.sphere.transform");
	print_material(&sphere->object.sphere.material, indent_level + 1, "sphere->object.sphere.material");
	print_computations(&sphere->object.sphere.comp, indent_level + 1, "sphere->object.sphere.comp");
	print_indented(indent_level, "}\n");
}

void	print_cone(t_object *cone, uint8_t indent_level, uint64_t object_index)
{
	(void)cone;
	(void)indent_level;
	(void)object_index;
}

void	print_cylinder(t_object *cylinder, uint8_t indent_level, uint64_t object_index)
{
	(void)cylinder;
	(void)indent_level;
	(void)object_index;
}

void	print_world(t_world *world, t_camera *camera)
{
	static t_print_object	printers[] = {
		print_plane,
		print_sphere,
		print_cone,
		print_cylinder
	};
	uint64_t	u;

	print_indented(0, "THE WORLD\n{\n");
	print_camera(camera, 1);
	u = 0;
	while (u < world->objects.len)
	{
		printers[((t_object *)vec_get(&world->objects, u))->type \
			- OBJECT_INDEX_OFFSET]
			((t_object *)vec_get(&world->objects, u), 1, u);
		u++;
	}
	u = 0;
	while (u < world->lights.len)
	{
		print_light((t_light *)vec_get(&world->lights, u), 1, u);
		u++;
	}
	print_indented(0, "}\n");
}

void	test_render(t_win *win)
{
	print_world(&win->world, &win->world.camera);
	render(win, &win->world.camera);
}

void	lighting_1(void)
{
	// t_world	world;
	t_tuple	pixel_point;
	t_comp	comps;
	t_light	light;
	t_tuple	final_colour;

	t_object	object_sphere;
	t_transform	transform;

	transform = (t_transform)
	{
		.translation = point(0, 0, 0),
		.rotation = point(0, 0, 0),
		.scale = point(1, 1, 1)
	};
	transform_object(&transform);
	object_sphere = sphere(
			point(0, 0, 0),
			transform,
			(t_material)
			{
				.colour = colour(1.0, 1.0, 1.0, 1.0),
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
	pixel_point.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1};
	comps.vectors.eye.tuple.units = (t_units){ 0.0, 0.0, -1.0, VECTOR_0};
	comps.vectors.surface_normal.tuple.units = (t_units){ 0.0, 0.0, -1.0, VECTOR_0};
	comps.vectors.in_shadow = 0;
	light.position.tuple.units = (t_units){0.0, 0.0, -10, POINT_1};
	light.intensity.tuple.units = (t_units){1.0, 1.0, 1.0, POINT_1};
	final_colour = lighting(object_sphere.object.sphere.material, &light, comps.vectors, pixel_point);
	printf("colour: %f, %f, %f, %f\n", final_colour.tuple.units.x, final_colour.tuple.units.y, final_colour.tuple.units.z, final_colour.tuple.units.w);
}

void	lighting_2(void)
{
	// t_world	world;
	t_tuple	pixel_point;
	t_comp	comps;
	t_light	light;
	t_tuple	final_colour;

	t_object	object_sphere;
	t_transform	transform;

	transform = (t_transform)
	{
		.translation = point(0, 0, 0),
		.rotation = point(0, 0, 0),
		.scale = point(1, 1, 1)
	};
	transform_object(&transform);
	object_sphere = sphere(
			point(0, 0, 0),
			transform,
			(t_material)
			{
				.colour = colour(1.0, 1.0, 1.0, 1.0),
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
	pixel_point.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1};
	comps.vectors.eye.tuple.units = (t_units){ 0.0, 0.7071, 0.7071, VECTOR_0};
	comps.vectors.surface_normal.tuple.units = (t_units){ 0.0, 0.0, -1.0, VECTOR_0};
	light.position.tuple.units = (t_units){0.0, 0.0, -10, POINT_1};
	light.intensity.tuple.units = (t_units){1.0, 1.0, 1.0, POINT_1};
	final_colour = lighting(object_sphere.object.sphere.material, &light, comps.vectors, pixel_point);
	// colour = lighting(((t_object *)vec_get(&world.objects, 0))->object.sphere.material, &light, comps.vectors, point);
	printf("colour: %f, %f, %f, %f\n", final_colour.tuple.units.x, final_colour.tuple.units.y, final_colour.tuple.units.z, final_colour.tuple.units.w);
}

void	lighting_3(void)
{
	// t_world	world;
	t_tuple	pixel_point;
	t_comp	comps;
	t_light	light;
	t_tuple	final_colour;

	t_object	object_sphere;
	t_transform	transform;

	transform = (t_transform)
	{
		.translation = point(0, 0, 0),
		.rotation = point(0, 0, 0),
		.scale = point(1, 1, 1)
	};
	transform_object(&transform);
	object_sphere = sphere(
			point(0, 0, 0),
			transform,
			(t_material)
			{
				.colour = colour(1.0, 1.0, 1.0, 1.0),
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
	pixel_point.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1};
	comps.vectors.eye.tuple.units = (t_units){ 0.0, 0.0, -1.0, VECTOR_0};
	comps.vectors.surface_normal.tuple.units = (t_units){ 0.0, 0.0, -1.0, VECTOR_0};
	light.position.tuple.units = (t_units){0.0, 0.0, 10, POINT_1};
	light.intensity.tuple.units = (t_units){1.0, 1.0, 1.0, POINT_1};
	final_colour = lighting(object_sphere.object.sphere.material, &light, comps.vectors, pixel_point);
	// colour = lighting(((t_object *)vec_get(&world.objects, 0))->object.sphere.material, &light, comps.vectors, point);
	printf("colour: %f, %f, %f, %f\n", final_colour.tuple.units.x, final_colour.tuple.units.y, final_colour.tuple.units.z, final_colour.tuple.units.w);
}

void	test_lighting(void)
{
	lighting_1();
	lighting_2();
	lighting_3();
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

void test_shadow(void)
{
	t_world world;
	t_tuple	p;

	t_light	light;

	light.position = point(-2, 2, -2);
	light.intensity = colour(1, 1, 1, 1);
	light.transform = default_transform_1();

	initialise_world(&world);
	default_world(&world);
	p.tuple.units = (t_units){0, 10, 0, POINT_1};
	is_shadow(&world, p, &light);
	if (world.shadow_hit.computations.vectors.in_shadow == 1)
		printf("in shadow\n");
	else
		printf("false\n");
}
// void	test_shading(void)
// {
// 	t_tuple	final_colour;
// 	t_world	world;

// 	initialise_world(&world);
// 	world.ray.origin.tuple.units = (t_units){ 0.0, 0.0, -5.0, POINT_1};
// 	world.ray.direction.tuple.units = (t_units){ 0.0, 0.0, 1.0, VECTOR_0};
// 	intersect_world(&world);
// 	identify_hit(&world);
// 	prepare_computations(&world);
// 	final_colour = shade_hit(&world);
// 	printf("colour: %f, %f, %f, %f\n", final_colour.tuple.units.x, final_colour.tuple.units.y, final_colour.tuple.units.z, final_colour.tuple.units.w);
// }

static void	vec_print_intersection(void *xs)
{
	printf("INTERSECTION:\n\tshape->type: %d\n",((t_intersect *)xs)->shape->type);
	printf("\tintersection->time %lf\n", ((t_intersect *)xs)->time);
}

void	test_plane_intersect_parallel_ray(t_win *win, t_object plane_test)
{
	t_ray		ray_test;

	printf("TEST_PLANE_INTERSECT_PARALLEL_RAY\n");
	ray_test = (t_ray){.origin = point(0, 10, 0), .direction = vector(0, 0, 1)};
	plane_intersection(ray_test, &plane_test, &win->world);
	vec_iter(&win->world.intersections, vec_print_intersection);
	printf("\n");
}

void	test_plane_intersect_coplanar_ray(t_win *win, t_object plane_test)
{
	t_ray		ray_test;

	printf("TEST_PLANE_INTERSECT_COPLANAR_RAY\n");
	ray_test = (t_ray){.origin = point(0, 0, 0), .direction = vector(0, 0, 1)};
	plane_intersection(ray_test, &plane_test, &win->world);
	vec_iter(&win->world.intersections, vec_print_intersection);
	printf("\n");
}

void	test_plane_intersect_from_above(t_win *win, t_object plane_test)
{
	t_ray		ray_test;

	printf("TEST_PLANE_INTERSECT_FROM_ABOVE\n");
	ray_test = (t_ray){.origin = point(0, 1, 0), .direction = vector(0, -1, 0)};
	plane_intersection(ray_test, &plane_test, &win->world);
	vec_iter(&win->world.intersections, vec_print_intersection);
	printf("\n");
}

void	test_plane_intersect_from_below(t_win *win, t_object plane_test)
{
	t_ray		ray_test;

	printf("TEST_PLANE_INTERSECT_FROM_BELOW\n");
	ray_test = (t_ray){.origin = point(0, -1, 0), .direction = vector(0, 1, 0)};
	plane_intersection(ray_test, &plane_test, &win->world);
	vec_iter(&win->world.intersections, vec_print_intersection);
	printf("\n");
}

void	test_plane(t_win *win)
{
	t_object	plane_b;

	vec_clear(&win->world.objects);
	plane_b = plane(plane_origin(), plane_transform(), plane_material());
	if (vec_push(&win->world.objects, &plane_b) == VEC_ERROR)
		handle_errors("unable to malloc for world object");
	// test_plane_normal();
	test_plane_intersect_parallel_ray(win, plane_b);
	test_plane_intersect_coplanar_ray(win, plane_b);
	test_plane_intersect_from_above(win, plane_b);
	test_plane_intersect_from_below(win, plane_b);
}

void	tests(void)
{
	// test_matrix_inversion();
	// test_red_disc();
	// test_normal_at_sphere();
	// test_reflect();
	// test_lighting_angled();
	// test_lighting_ambient();
	// test_3D_sphere();
	// test_3D_sphere_transformed();
	// test_3D_sphere_params();
	// test_view_transform();
	// test_lighting();
	// test_shadow();
	//	test_shading();
	// test_camera();
}

int	main(void)
{
	t_win	win;

	// if (argc != 2)
	//  	handle_errors(USAGE);
	//tests();
	 initialise_world(&win.world);
	// parse(&win);
	initialise_window(&win);
	// test_colour_at(&win);
	// test_render(&win);
	test_plane(&win);
	// // plot_points(&win);
	mlx_hook(win.win, KEY_DOWN, 0, handle_input, &win);
	mlx_loop(win.mlx);
	return (0);
}
