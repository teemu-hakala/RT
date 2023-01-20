











#include "RT.h"

bool	parse_boolean(t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "true", 4) == 0)
	{
		parser->c += sizeof("true") - 1;
		return (true);
	}
	else if (ft_strncmp(&parser->string[parser->c], "false", 5) == 0)
	{
		parser->c += sizeof("false") - 1;
		return (false);
	}
	else
		handle_errors("material syntax error: boolean");
	return (true);
}
