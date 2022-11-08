#include "RTv1.h"

t_pattern_colours	stripe_pattern(t_tuple a, t_tuple b)
{
	return ((t_pattern_colours){
		.a = a,
		.b = b
	});
}

t_tuple	none_at(t_material *material, t_tuple *point)
{
	(void)point;
	return (material->colour);
}

t_tuple	striped_at(t_material *material, t_tuple *point)
{
	if (fmod(floor(point->tuple.units.x), 2) == 0)
		return (material->pattern.colour.a);
	else
		return (material->pattern.colour.b);
}

t_tuple	checkered_at(t_material *material, t_tuple *point)
{
	(void)point;
	return (material->colour);
}

t_tuple	circle_at(t_material *material, t_tuple *point)
{
	(void)point;
	return (material->colour);
}

t_tuple	gradient_at(t_material *material, t_tuple *point)
{
	(void)point;
	return (material->colour);
}

t_tuple	pattern_at(t_material *material, t_tuple *point)
{
	static const t_pattern_at_fn	patterns[] = {
		none_at,
		striped_at,
		checkered_at,
		circle_at,
		gradient_at};

	return (patterns[material->pattern.type](material, point));
}