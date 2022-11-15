/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sub_objs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:07:04 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 10:52:24 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int	find_subobject_keyword(t_parser *parser, t_tuple *origin, \
	t_transform *transform, t_material *material)
{
	find_double_quote(parser);
	if (ft_strncmp(&parser->string[parser->c], "origin\"", 7) == 0)
	{
		parser->c += sizeof("origin\"") - 1;
		find_colon(parser);
		parse_tuple(origin, parser);
		return (true);
	}
	else if (ft_strncmp(&parser->string[parser->c], "transform\"", 10) == 0)
	{
		parser->c += sizeof("transform\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		if (find_matching_bracket(parser))
			return (true);
		parse_transform(transform, parser);
		return (true);
	}
	else if (ft_strncmp(&parser->string[parser->c], "material\"", 9) == 0)
	{
		parser->c += sizeof("material\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		if (find_matching_bracket(parser))
			return (true);
		parse_material(material, parser);
		return (true);
	}
	return (false);
}

void	parse_tuple(t_tuple *tuple, t_parser *parser)
{
	int	i;

	i = 0;
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c++] == '[')
	{
		while (i < 3)
		{
			tuple->array[i] = rt_atof(parser);
			if (i < 2 && parser->string[parser->c++] != ',')
				handle_errors("array syntax error");
			i++;
		}
		if (parser->string[parser->c] == ']')
		{
			parser->c++;
			return ;
		}
	}
	handle_errors("DENIED: parse_tuple");
}

void	find_max(t_object *object, t_parser *parser)
{
	int	max;

	parser->c += sizeof("max\"") - 1;
	find_colon(parser);
	max = rt_atof(parser);
	if (object->type == OBJECT_CONE)
		object->object.cone.max = max;
	else
		object->object.cylinder.max = max;
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		find_min_and_max(object, parser);
	}
}

/* find min and max is currently not being used. Need to put it into function*/

int	find_min_and_max(t_object *object, t_parser *parser)
{
	t_fl	min;
	int		closed;

	find_double_quote(parser);
	if (!ft_strncmp(&parser->string[parser->c], "min\"", 4))
	{
		parser->c += sizeof("min\"") - 1;
		find_colon(parser);
		min = rt_atof(parser);
		if (object->type == OBJECT_CONE)
			object->object.cone.min = min;
		else
			object->object.cylinder.min = min;
		parser->c += ft_clear_whitespace(&parser->string[parser->c]);
		if (parser->string[parser->c] == ',')
		{
			parser->c++;
			find_min_and_max(object, parser);
		}
	}
	else if (!ft_strncmp(&parser->string[parser->c], "max\"", 4))
	{
		find_max(object, parser);
	}
	else if (!ft_strncmp(&parser->string[parser->c], "closed\"", 7))
	{
		parser->c += sizeof("closed\"") - 1;
		find_colon(parser);
		parser->c += ft_clear_whitespace(&parser->string[parser->c]);
		if (parser->string[parser->c] == '1')
			closed = true;
		else if (parser->string[parser->c] == '0')
			closed = false;
		else
			handle_errors("cone/cylinder syntax error");
		if (object->type == OBJECT_CONE)
			object->object.cone.closed = closed;
		else
			object->object.cylinder.closed = closed;
	}
	else
		return (false);
	return (true);
}
