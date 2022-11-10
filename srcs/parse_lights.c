#include "RTv1.h"

t_light	default_light(void)
{
	return ((t_light){
		.position = point(-10, 10, -10),
		.intensity = colour(1, 1, 1, 1),
		.transform = default_transform_1(),
	});
}

int	find_light_subobject_keyword(t_light *light, t_vec *brackets, \
	char *string, uint64_t *c)
{
	find_double_quote(string, c);
	if (ft_strncmp(&string[*c], "position\"", 9) == 0)
	{
		*c += 9;
		parse_tuple(&light->position, string, c);
		return (1);
	}
	else if (ft_strncmp(&string[*c], "transform\"", 10) == 0)
	{
		parse_transform(&light->transform, brackets, string, c);
		return (1);
	}
	else if (ft_strncmp(&string[*c], "intensity\"", 10) == 0)
	{
		*c += 10;
		parse_tuple(&light->intensity, string, c);
		return (1);
	}
	else
		return (0);
}

void	parse_light(t_vec *brackets, char *string, uint64_t *c, t_light *light)
{
	find_colon(string, c);
	find_open_bracket(brackets, string, c);
	if (find_matching_bracket(brackets, string, c))
		return ;
	else
	{
		while (find_light_subobject_keyword(&light, brackets, string, c))
			parse_light(brackets, string, c, light);
		if (!find_matching_bracket(brackets, string, c))
			handle_errors("syntax error");
	}
}

int	find_light(char *string, uint64_t *c)
{
	find_double_quote(string, c);
	if (ft_strncmp(&string[*c], "light\"", 6) == 0)
		return (true);
	return (false);
}

void	parse_lights(t_world *world, t_vec *brackets, char *string, uint64_t *c)
{
	t_light	light;

	find_colon(string, c);
	find_open_bracket(brackets, string, c);
	find_open_bracket(brackets, string, c);
	while (find_light(string, c))
	{
		light = default_light();
		parse_light(brackets, string, c, &light);
		if (vec_push(&world->lights, &light) == VEC_ERROR)
			handle_errors("vec_push light error");
	}
}