#include "RTv1.h"

void	parse_tuple(t_tuple *tuple, char *string, uint64_t *c)
{
	int i;

	i = 0;
	find_colon(string, c);
	*c += ft_clear_whitespace(string);
	if (string[*c] == '[')
	{
		//*c += ft_clear_whitespace(string);
		//doesn't atof clear the whitespace anyway?
		while (i < 3)
		{
			tuple->array[i] = rt_atof(&string, c);
			if (i < 2 && ++c != ',')
				handle_errors("array syntax error");
			i++;
		}
		if (string[++*c] == ']')
		{
			c++;
			return ;
		}
	}
	handle_errors("DENIED: parse_tuple");
}

int	find_transform_keyword(t_transform *transform, t_vec *brackets, \
	char *string, uint64_t *c)
{
	find_double_quote(string, c);
	if (ft_strncmp(&string[*c], "translation\"", 12) == 0)
	{
		*c += 12;
		parse_tuple(&transform->translation, string, c);
		return (1);
	}
	else if (ft_strncmp(&string[*c], "rotation\"", 9) == 0)
	{
		*c += 9;
		parse_tuple(&transform->rotation, string, c);
		return (1);
	}
	else if (ft_strncmp(&string[*c], "scale\"", 6) == 0)
	{
		*c += 6;
		parse_tuple(&transform->scale, string, c);
		return (1);
	}
	else
		return (0);
}

void	parse_transform(t_transform *transform, t_vec *brackets, \
	char *string, uint64_t *c)
{
	c += 10;
	find_colon(string, c);
	find_open_bracket(brackets, string, c);
	if (find_matching_bracket(brackets, string, c))
		return ;
	else
	{
		while (find_transform_keyword(&transform, brackets, string, c))
			parse_transform(transform, brackets, string, c);
		if (!find_matching_bracket(brackets, string, c))
			handle_errors("syntax error");
	}
}

void	parse_material(t_material *material, t_vec *brackets, \
	char *string, uint64_t *c)
{

}

