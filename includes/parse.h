#ifndef PARSE_H
# define PARSE_H

# include "RTv1.h"

typedef struct s_parser
{
	t_vec		brackets;
	char		*string;
	uint64_t	c;
	uint64_t	atof_index;
}				t_parser;

typedef int	(*t_subobject_keyword_fn)(t_parser *, t_object *);

/*parse objects*/
void	parse_lights(t_world *world, t_parser *parser);
int		dispatch_find_subobject_keyword(t_parser *parser, t_object *shape);

/*parse sub-objects*/
void	parse_tuple(t_tuple *tuple, t_parser *parser);
void	parse_transform(t_transform *transform, t_parser *parser);
void	parse_material(t_material *material, t_parser *parser);
/*utility parse functions*/
void	find_open_bracket(t_parser *parser);
int		find_matching_bracket(t_parser *parser);
void	find_double_quote(t_parser *parser);
void	find_colon(t_parser *parser);
double	rt_atof(t_parser *parser);

#endif
