











#include "RTv1.h"

void	find_open_bracket(t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == '{' || parser->string[parser->c] == '[')
	{
		if (vec_push_arr(&parser->brackets, &parser->string[parser->c++], 1) \
			== VEC_ERROR)
			handle_errors("vec_push_arr error");
	}
	else
		handle_errors("open bracket format error");
}

int	find_matching_bracket(t_parser *parser)
{
	char	open_bracket;
	char	close_bracket;

	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	open_bracket = ((char *)parser->brackets.memory)[parser->brackets.len - 1];
	close_bracket = open_bracket + (open_bracket & 0x1U) + 1;
	if (parser->string[parser->c] != close_bracket)
		return (false);
	parser->brackets.len--;
	parser->c++;
	return (true);
}

void	find_colon(t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] != ':')
		handle_errors("colon format error");
	parser->c++;
}
