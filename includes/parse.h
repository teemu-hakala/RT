#ifndef PARSE_H
# define PARSE_H

/*parse objects*/
void	parse_lights(t_world *world, t_vec *brackets, char *string, uint64_t *c);

/*parse sub-objects*/
void	parse_tuple(t_tuple *tuple, char *string, uint64_t *c);
void	parse_transform(t_transform *transform, t_vec *brackets,\
	char *string, uint64_t *c);
void	parse_material(t_material *material, t_vec *brackets, \
	char *string, uint64_t *c);
/*utility parse functions*/
void	find_open_bracket(t_vec *brackets, char *string, uint64_t *c);
int		find_matching_bracket(t_vec *brackets, char *string, uint64_t *c);
void	find_double_quote(char *string, uint64_t *c);
void	find_colon(char *string, uint64_t *c);

#endif