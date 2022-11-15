// #include "RTv1.h"

// t_pattern	default_stripe_pattern(void)
// {
// 	return ((t_pattern){
// 		.type = PATTERN_STRIPE,
// 		.colour = set_pattern_colours(hex_to_argb(COLOUR_BLACK), \
// 			hex_to_argb(COLOUR_WHITE)),
// 		.transform = default_transform_2()
// 	});
// }

// t_pattern	default_gradient_pattern(void)
// {
// 	return ((t_pattern){
// 		.type = PATTERN_GRADIENT,
// 		.colour = set_pattern_colours(hex_to_argb(COLOUR_WHITE), \
// 			hex_to_argb(COLOUR_RED)),
// 		.transform = default_transform_1()
// 	});
// }

// t_pattern	default_ring_pattern(void)
// {
// 	return ((t_pattern){
// 		.type = PATTERN_CIRCLES,
// 		.colour = set_pattern_colours(hex_to_argb(COLOUR_RED),\
// 			hex_to_argb(COLOUR_BLACK)),
// 		.transform = default_transform_1()
// 	});
// }

// t_pattern	default_checkered_pattern(void)
// {
// 	return ((t_pattern){
// 		.type = PATTERN_CHECKERED,
// 		.colour = set_pattern_colours(hex_to_argb(COLOUR_WHITE),\
// 			hex_to_argb(COLOUR_BLACK)),
// 		.transform = default_transform_1()
// 	});
// }

// static t_material	default_pattern_mat(void)
// {
// 	return ((t_material){
// 		.ambient = 0.1,
// 		.diffuse = 0.9,
// 		.specular = 0.9,
// 		.shininess = 200,
// 		.init_colour = colour(1.0, 1.0, 1.0, 1.0),
// 		.pattern = default_checkered_pattern(),
// 		.col_mash = vector(0, 0, 0),
// 		.amb_col = vector(0, 0, 0),
// 		.dif_col = vector(0, 0, 0),
// 		.spec_col = vector(0, 0, 0)
// 	});
// }

// // static t_light	default_light(void)
// // {
// // 	return ((t_light){
// // 		.position = point(-10, 10, -10),
// // 		.intensity = colour(1, 1, 1, 1),
// // 		.transform = default_transform_1(),
// // 	});
// // }

// void	pattern_world(t_world *world)
// {
// 	t_object	sphere_1;
// 	t_mtx		view_matrix;
// 	t_light		light;

// 	sphere_1 = sphere(default_origin(), default_transform_1(),
// 			default_pattern_mat());
// 	world->camera = camera(camera_origin(), camera_transform(), M_PI_2, default_canvas());
// 	view_matrix = view_transform(world->camera.origin, point(0, 0, 0), vector(0, 1, 0));
// 	matrix_multi_square(&world->camera.transform.matrix, &view_matrix, 4);
// 	world->camera.transform.inverse = world->camera.transform.matrix;
// 	matrix_inversion(&world->camera.transform.inverse, 4);
// 	if (vec_push(&world->objects, &sphere_1) == VEC_ERROR)
// 		handle_errors("unable to malloc for world object");
// 	light = default_light();
// 	if (vec_push(&world->lights, &light) == VEC_ERROR)
// 		handle_errors("unable to malloc for light");
// }
