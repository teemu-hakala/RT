#include "RT.h"

t_tuple	apply_sepia(t_tuple original)
{
	t_tuple	temp;

	temp.tuple.colour.r = (original.tuple.colour.r * 0.393) + \
		(original.tuple.colour.g * 0.769) + \
		(original.tuple.colour.b * 0.189);
	temp.tuple.colour.g = (original.tuple.colour.r * 0.349) + \
		(original.tuple.colour.g *  0.686) + \
		(original.tuple.colour.b *  0.168);
	temp.tuple.colour.b = (original.tuple.colour.r * 0.272) + \
		(original.tuple.colour.g *  0.534) + \
		(original.tuple.colour.b *  0.131);
	return (temp);
}

t_tuple	apply_filter(t_world *world, t_tuple colour)
{
	if (world->filter == SEPIA)
		return (apply_sepia(colour));
	else
		return (colour);
}
