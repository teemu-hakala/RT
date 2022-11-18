/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_cylinder_subobj.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:12:31 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/18 13:22:16 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	find_min(t_parser *parser, t_object *object)
{
	int	min;

	parser->c += sizeof("\"min\"") - 1;
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
		cone_and_cylinder_objects(parser, object);
	}
}

void	find_max(t_parser *parser, t_object *object)
{
	int	max;

	parser->c += sizeof("\"max\"") - 1;
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
		cone_and_cylinder_objects(parser, object);
	}
}

void	find_closed(t_parser *parser, t_object *object)
{
	int		closed;

	parser->c += sizeof("\"closed\"") - 1;
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
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		cone_and_cylinder_objects(parser, object);
	}
}

int	cone_and_cylinder_objects(t_parser *parser, t_object *object)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (!ft_strncmp(&parser->string[parser->c], "\"min\"", 5))
		find_min(parser, object);
	else if (!ft_strncmp(&parser->string[parser->c], "\"max\"", 5))
		find_max(parser, object);
	else if (!ft_strncmp(&parser->string[parser->c], "\"closed\"", 8))
		find_closed(parser, object);
	else
		return (false);
	return (true);
}
