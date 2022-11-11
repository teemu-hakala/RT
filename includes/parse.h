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
void	parse_into(t_world *world, const int file_descriptor);
double	rt_atof(t_parser *parser);
/*parse objects*/
void		parse_lights(t_world *world, t_parser *parser);
void		parse_camera(t_world *world, t_parser *parser);
void		parse_shapes(t_world *world, t_parser *parser);
void		parse_plane(t_parser *parser, t_object *shape);
void		parse_sphere(t_parser *parser, t_object *shape);
void		parse_cone(t_parser *parser, t_object *shape);
void		parse_cylinder(t_parser *parser, t_object *shape);
/*parse sub-objects*/
int			dispatch_find_subobject_keyword(t_parser *parser, t_object *shape);
void		parse_tuple(t_tuple *tuple, t_parser *parser);
void		parse_transform(t_transform *transform, t_parser *parser);
void		parse_material(t_material *material, t_parser *parser);

/*utility parse functions*/
void		find_open_bracket(t_parser *parser);
int			find_matching_bracket(t_parser *parser);
void		find_double_quote(t_parser *parser);
void		find_colon(t_parser *parser);

/*default settings*/
t_tuple		default_origin(void);
t_transform	default_transform_1(void);
t_material	default_phong_mat(void);
t_material	default_material_1(void);
t_light		default_light(void);

/*object prototypes*/
t_camera	camera_prototype(void);
t_object	plane_prototype(void);
t_object	sphere_prototype(void);
t_object	cone_prototype(void);
t_object	cylinder_prototype(void);

#endif
