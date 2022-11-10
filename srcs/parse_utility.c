
#include "RTv1.h"

void	find_open_bracket(t_vec *brackets, char *string, uint64_t *c)
{
	*c += ft_clear_whitespace(string);
	if (string[*c] == '{'|| string[*c] == '[')
	 	if (vec_push_arr(brackets, &string[*c++], 1) == VEC_ERROR)
			handle_errors("vec_push_arr error");
	else
		handle_errors("bracket format error");
}

int	find_matching_bracket(t_vec *brackets, char *string, uint64_t *c)
{
	char	open_bracket;
	char	close_bracket;

	*c += ft_clear_whitespace(string);
	open_bracket = ((char *)brackets->memory)[brackets->len - 1];
	close_bracket = open_bracket + (open_bracket & 0x1U) + 1;
	if (string[*c] != close_bracket)
		return (false);
	brackets->len--;
	*c++;
	return (true);
}

void	find_double_quote(char *string, uint64_t *c)
{
	*c += ft_clear_whitespace(string);
	if (string[*c] != '"')
		handle_errors("bracket format error");
	*c++;
}

void	find_colon(char *string, uint64_t *c)
{
	*c += ft_clear_whitespace(string);
	if (string[*c] != ':')
		handle_errors("bracket format error");
	*c++;
}