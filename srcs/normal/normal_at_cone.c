#include "RT.h"

t_tuple	normal_at_cone(void *cone, t_tuple *point_at)
{
	t_fl	distance;
	t_fl	y;
	t_tuple	obj_pt;

	obj_pt = matrix_tuple_multi(&((t_cone *)cone)->transform.inverse, point_at);
	y = sqrt((obj_pt.tuple.units.x * obj_pt.tuple.units.x) + \
		(obj_pt.tuple.units.z * obj_pt.tuple.units.z));
	if (obj_pt.tuple.units.y > 0)
		y *= -1;
	distance = (obj_pt.tuple.units.x * obj_pt.tuple.units.x) + \
		(obj_pt.tuple.units.z * obj_pt.tuple.units.z);
	if (distance < 1 && (obj_pt.tuple.units.y >= \
		((((t_object *)cone)->object.cone.max) - EPSILON)))
		return (normalize(object_to_world_space(\
			&((t_object *)cone)->object.cone.transform.inverse, \
			vector(0, 1, 0))));
	else if (distance < 1 && (obj_pt.tuple.units.y <= \
		((((t_object *)cone)->object.cone.min) + EPSILON)))
		return ((normalize(object_to_world_space(\
			&((t_object *)cone)->object.cone.transform.inverse, \
			vector(0, -1, 0)))));
	else
		return (normalize(object_to_world_space(\
			&((t_object *)cone)->object.cone.transform.inverse, \
			vector(obj_pt.tuple.units.x, y, obj_pt.tuple.units.z))));
}
