#include "RTv1.h"

t_tuple shade_hit(t_world *world, t_comp *shape_comps)
{
	t_tuple colour;
	t_object	*shape;
	uint64_t	i;

	shape = (t_object *)vec_get(&world->objects, world->object_index);
	shape->type = shape_comps->type;
	colour.tuple.units = (t_units) {0.0, 0.0, 0.0, 0.0};
	i = 0;
	while (i < world->lights.len)
	{
		if (shape->type == OBJECT_PLANE)
		{
			colour = tuple_add((lighting(shape->object.plane.material, \
			(*(t_light *)vec_get(&world->lights, i)),shape_comps->vectors, \
			shape_comps->point)), colour);
		}
		if (shape->type == OBJECT_SPHERE)
		{
			colour = tuple_add((lighting(shape->object.sphere.material, \
			(*(t_light *)vec_get(&world->lights, i)),shape_comps->vectors, \
			shape_comps->point)), colour);
		}
		if (shape->type == OBJECT_CONE)
		{
			colour = tuple_add((lighting(shape->object.cone.material, \
			(*(t_light *)vec_get(&world->lights, i)),shape_comps->vectors, \
			shape_comps->point)), colour);
		}
		if (shape->type == OBJECT_CYLINDER)
		{
			colour = tuple_add((lighting(shape->object.cylinder.material, \
			(*(t_light *)vec_get(&world->lights, i)),shape_comps->vectors, \
			shape_comps->point)), colour);
		}
		i++;
	}
	printf("colour: a: %f, r: %f, g: %f, b:%f\n", colour.tuple.colour.a, \
		colour.tuple.colour.r, colour.tuple.colour.g, colour.tuple.colour.b);
	return (colour);
}



