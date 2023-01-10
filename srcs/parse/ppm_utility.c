#include "RT.h"

static int	check_for_comments(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '#')
			return (1);
		i++;
	}
	return (0);
}

void	read_ppm_contents(t_vec *string, const int file_descriptor)
{
	char	*line;
	int		read_bytes;
	int		gnl_status;
	char	first;

	first = true;
	while (1)
	{
		gnl_status = gnl_read_ret(file_descriptor, &line, &read_bytes);
		if (gnl_status == 0)
			break ;
		if (gnl_status < 0)
			handle_errors("DENIED: get_next_line error");
		if (first)
		{
			if (vec_new(string, read_bytes * 4, sizeof(char)) == VEC_ERROR)
				handle_errors("vec_new error");
			first = false;
		}
		if (check_for_comments(line) == true)
		{
			free (line);
			continue ;
		}
		if (vec_push_arr(string, line, ft_strlen(line)) == VEC_ERROR)
			handle_errors("vec_push_arr error");
		free (line);
	}
	if (vec_push_arr(string, "\0", 1) == VEC_ERROR)
		handle_errors("vec_push_arr error");
}

void	parse_name(t_ppm_image *image, t_parser *parser)
{
	uint64_t	length;
	uint64_t	i;

	length = 0;
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] != '"')
		handle_errors("ppm file name syntax error");
	parser->c++;
	i = parser->c;
	while (parser->string[i] && parser->string[i] != '"')
		i++;
	length = i - parser->c;
	image->name = ft_strsub(parser->string, parser->c, length);
	parser->c += length + 1;
}
