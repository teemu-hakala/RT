
#include "RT.h"

static void	parse_texture_type(t_texture *texture, t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"checkered\"", 11) == 0)
	{
		parser->c += sizeof("\"checkered\"") - 1;
		texture->type = TEXTURE_CHECKERED;
		*texture = default_checkered_texture();
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"align_check\"", 13) == 0)
	{
		parser->c += sizeof("\"align_check\"") - 1;
		texture->type = TEXTURE_ALIGN_CHECK;
		*texture = default_align_check();
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"external\"", 10) == 0)
	{
		parser->c += sizeof("\"external\"") - 1;
		texture->type = TEXTURE_EXTERNAL;
		*texture = default_external();
	}
	else
		handle_errors("not a texture type");
}

static void	parse_final_texture(t_texture *texture, t_parser *parser)
{
	if (ft_strncmp(&parser->string[parser->c], "\"transform\"", 11) == 0)
	{
		parse_transform_subobject(parser, &texture->transform);
		transform_object(&texture->transform);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"name\"", 6) == 0)
	{
		parser->c += sizeof("\"name\"") - 1;
		find_colon(parser);
		parse_name(&texture->image[0], parser);
		open_ppm(&texture->image[0]);
	}
	else
		handle_errors("texture keyword syntax error");
}

static void	parse_texture_cont(t_texture *texture, t_parser *parser)
{
	if (ft_strncmp(&parser->string[parser->c], "\"colour_a\"", 10) == 0)
	{
		parser->c += sizeof("\"colour_a\"") - 1;
		find_colon(parser);
		parse_tuple(&texture->colour_a, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"colour_b\"", 10) == 0)
	{
		parser->c += sizeof("\"colour_b\"") - 1;
		find_colon(parser);
		parse_tuple(&texture->colour_b, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"face\"", 6) == 0)
	{
		parser->c += sizeof("\"face\"") - 1;
		find_colon(parser);
		parse_face(texture, parser);
	}
	else
		parse_final_texture(texture, parser);
}

static void	parse_texture_keywords(t_texture *texture, t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"type\"", 6) == 0)
	{
		parser->c += sizeof("\"type\"") - 1;
		find_colon(parser);
		parse_texture_type(texture, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"width\"", 7) == 0)
	{
		parser->c += sizeof("\"width\"") - 1;
		find_colon(parser);
		texture->width = rt_atoi(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"height\"", 8) == 0)
	{
		parser->c += sizeof("\"height\"") - 1;
		find_colon(parser);
		texture->height = rt_atoi(parser);
	}
	else
		parse_texture_cont(texture, parser);
}

void	parse_texture(t_texture *texture, t_parser *parser)
{
	parse_texture_keywords(texture, parser);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		parse_texture(texture, parser);
	}
	else
	{
		if (find_matching_bracket(parser))
		{
			transform_object(&texture->transform);
			return ;
		}
		else
			handle_errors("texture syntax error");
	}
}
