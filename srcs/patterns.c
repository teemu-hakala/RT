#include "RTv1.h"

t_pattern_colours	stripe_pattern(t_tuple a, t_tuple b)
{
	return ((t_pattern_colours){
		.a = a,
		.b = b
	});
}

void	none_at(t_material *material, t_tuple *point, t_transform transform)
{
	(void)point;
	(void)transform;
	material->final_colour = material->init_colour;
}

void	striped_at(t_material *material, t_tuple *point, t_transform transform)
{
	t_tuple	object_space;
	t_tuple	pattern_space;

	material->final_colour = material->init_colour;
	object_space = matrix_tuple_multi(&transform.inverse, point);
	pattern_space = matrix_tuple_multi(&material->pattern.transform.inverse, &object_space);

	if (fmod(floor(pattern_space.tuple.units.x), 2) == 0)
		material->final_colour = material->pattern.colour.a;
	else
		material->final_colour = material->pattern.colour.b;
}

void	checkered_at(t_material *material, t_tuple *point, t_transform transform)
{
	(void)point;
	(void)transform;
	material->final_colour = material->init_colour;
}

void	circle_at(t_material *material, t_tuple *point, t_transform transform)
{
	(void)point;
	(void)transform;
	material->final_colour = material->init_colour;
}

void	gradient_at(t_material *material, t_tuple *point, t_transform transform)
{
	(void)point;
	(void)transform;
	material->final_colour = material->init_colour;
}

void	pattern_at(t_material *material, t_tuple *point, t_transform transform)
{
	static const t_pattern_at_fn	patterns[] = {
		none_at,
		striped_at,
		checkered_at,
		circle_at,
		gradient_at};

	return (patterns[material->pattern.type](material, point, transform));
}