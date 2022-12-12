











#include "RT.h"

t_tuple	default_origin(void)
{
	return (point(0, 0, 0));
}

t_transform	default_transform_1(void)
{
	t_transform	d;

	d.translation = point(0, 0, 0);
	d.rotation = point(0, 0, 0);
	d.scale = point(1, 1, 1);
	transform_object(&d);
	return (d);
}

t_transform	default_transform_2(void)
{
	t_transform	d;

	d.translation = point(0, 0, 0);
	d.rotation = point(0, 0, 0);
	d.scale = point(0.3, 0.3, 0.3);
	transform_object(&d);
	return (d);
}

t_material	default_phong_mat(void)
{
	return ((t_material){
		.ambient = 0.1,
		.diffuse = 0.9,
		.specular = 0.9,
		.shininess = 200,
		.init_colour = vector(1.0, 1.0, 1.0),
		.col_mash = vector(0, 0, 0)
	});
}

t_material	default_material_1(void)
{
	return ((t_material){
		.ambient = 0.1,
		.diffuse = 0.7,
		.specular = 0.2,
		.shininess = 200,
		.init_colour = vector(0.8, 1.0, 0.6),
		.col_mash = vector(0, 0, 0)
	});
}

t_canvas	default_canvas(void)
{
	return ((t_canvas){.vertical = HEIGHT, .horizontal = WIDTH});
}
