/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sub_objs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:07:04 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 10:07:07 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int	find_subobject_keyword(t_parser *parser,
	t_tuple *origin,
	t_transform *transform,
	t_material *material)
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

int	plane_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, &shape->object.plane.origin,
		&shape->object.plane.transform,
		&shape->object.plane.material));
}

int	sphere_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, &shape->object.sphere.origin,
		&shape->object.sphere.transform,
		&shape->object.sphere.material));
}

int	cone_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, &shape->object.cone.origin,
		&shape->object.cone.transform,
		&shape->object.cone.material));
}

int	cylinder_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, &shape->object.cylinder.origin,
		&shape->object.cylinder.transform,
		&shape->object.cylinder.material));
}

int	dispatch_find_subobject_keyword(t_parser *parser, t_object *shape)
{
	static const t_subobject_keyword_fn	kw_fns[] =
	{
		plane_subobject_keywords,
		sphere_subobject_keywords,
		cone_subobject_keywords,
		cylinder_subobject_keywords
	};

	return (kw_fns[shape->type - OBJECT_INDEX_OFFSET](parser, shape));
}

void	parse_tuple(t_tuple *tuple, t_parser *parser)
{
	int i;

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

int	find_transform_keywords(t_transform *transform, t_parser *parser)
{
	find_double_quote(parser);
	if (ft_strncmp(&parser->string[parser->c], "translation\"", 12) == 0)
	{
		parser->c += sizeof("translation\"") - 1;
		find_colon(parser);
		parse_tuple(&transform->translation, parser);
		return (true);
	}
	else if (ft_strncmp(&parser->string[parser->c], "rotation\"", 9) == 0)
	{
		parser->c += sizeof("rotation\"") - 1;
		find_colon(parser);
		parse_tuple(&transform->rotation, parser);
		return (true);
	}
	else if (ft_strncmp(&parser->string[parser->c], "scale\"", 6) == 0)
	{
		parser->c += sizeof("scale\"") - 1;
		find_colon(parser);
		parse_tuple(&transform->scale, parser);
		return (true);
	}
	return (false);
}

void	parse_transform(t_transform *transform, t_parser *parser)
{
	find_transform_keywords(transform, parser);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		parse_transform(transform, parser);
	}
	else
	{
		if (find_matching_bracket(parser))
			return ;
		else
			handle_errors("transform syntax error");
	}
}

void	find_material_keywords(t_material *material, t_parser *parser)
{
	find_double_quote(parser);
	if (ft_strncmp(&parser->string[parser->c], "ambient\"", 8) == 0)
	{
		parser->c += sizeof("ambient\"") - 1;
		find_colon(parser);
		material->ambient = rt_atof(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "diffuse\"", 8) == 0)
	{
		parser->c += sizeof("diffuse\"") - 1;
		find_colon(parser);
		material->diffuse = rt_atof(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "specular\"", 9) == 0)
	{
		parser->c += sizeof("specular\"") - 1;
		find_colon(parser);
		material->specular = rt_atof(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "shininess\"", 10) == 0)
	{
		parser->c += sizeof("shininess\"") - 1;
		find_colon(parser);
		material->shininess = rt_atof(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "init_colour\"", 12) == 0)
	{
		parser->c += sizeof("init_colour\"") - 1;
		find_colon(parser);
		parse_tuple(&material->init_colour, parser);
	}
	// else if (ft_strncmp(&parser->string[parser->c], "pattern\"", 8) == 0)
	// {
	// 	parser->c += sizeof("pattern\"") - 1;
	// }
	else
		handle_errors("material syntax error");
}

void	parse_material(t_material *material, t_parser *parser)
{
	find_material_keywords(material, parser);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		parse_material(material, parser);
	}
	else
	{
		if (find_matching_bracket(parser))
			return ;
		else
			handle_errors("material syntax error");
	}
}

