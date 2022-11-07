#include "RTv1.h"

t_patterns	stripe_pattern(t_tuple a, t_tuple b)
{
	return ((t_patterns){
		.a = a,
		.b = b
	});
}

t_tuple	stripe_at(t_patterns pattern, t_tuple point)
{
	if (fmod(point.tuple.units.x, 2) == 0)
		return (pattern.a);
	else
		return (pattern.b);
}