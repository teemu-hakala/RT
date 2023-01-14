











#include "RT.h"

void	initialise_front_vecs(t_vec *positive_front_ids, \
	t_vec *negative_front_ids)
{
	if (positive_front_ids->memory == NULL \
		&& vec_new(positive_front_ids, 128, sizeof(uint64_t)) == VEC_ERROR)
		handle_errors("positive_front_ids vec initialisation error");
	if (negative_front_ids->memory == NULL \
		&& vec_new(negative_front_ids, 128, sizeof(uint64_t))== VEC_ERROR)
		handle_errors("negative_front_ids vec initialisation error");
}

bool	back_matcher_by_id(void *hay, void *needle)
{
	const uint64_t	hay_shape_id = *(uint64_t *)hay;
	const uint64_t	needle_shape_id = *(uint64_t *)needle;

	if (hay_shape_id == needle_shape_id)
		return (true);
	return (false);
}

void	volume_negator(t_world *world, t_vec *front, t_object *shape)
{
	t_vec_find_result	find_result;

	(void)world;
	find_result = vec_find(front, back_matcher_by_id, &shape->id, \
		VEC_BEGINNING);
	if (find_result.result == NULL)
	{
		if (vec_push_arr(front, &shape->id, 1) \
			== VEC_ERROR)
			handle_errors("vec_push find_result error");
	}
	else
		vec_remove(front, find_result.at);
}

void	identify_hit(t_world *world, t_hit *hit)
{
	t_vec			positive_front_ids;
	t_vec			negative_front_ids;
	t_intersect		*intersection;
	uint64_t		i;

	positive_front_ids.memory = NULL;
	negative_front_ids.memory = NULL;
	initialise_front_vecs(&positive_front_ids, &negative_front_ids);
	i = 0;
	hit->hit_check = false;
	while (i < world->intersections.len)
	{
		intersection = \
			(t_intersect *)vec_get(&world->intersections, i++);
		if (is_positive_object(intersection->shape))
			volume_negator(world, &positive_front_ids, intersection->shape);
		else
			volume_negator(world, &negative_front_ids, intersection->shape);
		if (intersection->time >= 0)
		{
			hit->intersection = *intersection;
			hit->hit_check = true;
			break ;
		}
	}
	free(positive_front_ids.memory);
	free(negative_front_ids.memory);
}