











#ifndef PARSE_H
# define PARSE_H

# include "RT.h"

typedef struct s_parser
{
	t_vec		brackets;
	char		*string;
	uint64_t	c;
	uint64_t	atof_index;
}				t_parser;

typedef int	(*t_subobject_keyword_fn)(t_parser *, t_object *);
void		parse_into(t_world *world, const int file_descriptor);
double		rt_atof(t_parser *parser);
/*parse objects*/
void		parse_lights(t_world *world, t_parser *parser);
void		parse_single_light(t_parser *parser, t_light *light);
void		parse_camera(t_world *world, t_parser *parser);
void		parse_shapes(t_world *world, t_parser *parser);
void		parse_plane(t_parser *parser, t_object *shape);
void		parse_sphere(t_parser *parser, t_object *shape);
void		parse_cone(t_parser *parser, t_object *shape);
void		parse_cylinder(t_parser *parser, t_object *shape);
void		parse_cube(t_parser *parser, t_object *shape);
/*parse sub-objects*/
int			find_subobject_keyword(t_parser *parser, t_transform *transform, \
			t_material *material, t_pattern *pattern);
int			dispatch_find_subobject_keyword(t_parser *parser, t_object *shape);
int			plane_subobject_keywords(t_parser *parser, t_object *shape);
int			sphere_subobject_keywords(t_parser *parser, t_object *shape);
int			cone_subobject_keywords(t_parser *parser, t_object *shape);
int			cylinder_subobject_keywords(t_parser *parser, t_object *shape);
int			cube_subobject_keywords(t_parser *parser, t_object *shape);
void		parse_tuple(t_tuple *tuple, t_parser *parser);
void		parse_transform(t_transform *transform, t_parser *parser);
void		parse_transform_subobject(t_parser *parser, t_transform *transform);
void		parse_material(t_material *material, t_parser *parser);
void		parse_pattern(t_pattern *pattern, t_parser *parser);
void		parse_face(t_pattern *pattern, t_parser *parser);
int			cone_and_cylinder_objects(t_parser *parser, t_object *object);

/*utility parse functions*/
void		find_open_bracket(t_parser *parser);
int			find_matching_bracket(t_parser *parser);
void		find_colon(t_parser *parser);

/*default settings*/
t_tuple		default_origin(void);
t_transform	default_transform_1(void);
t_transform	default_transform_2(void);
void		transform_camera(t_camera *camera);
t_material	default_phong_mat(void);
t_material	default_material_1(void);
t_canvas	default_canvas(void);

/*object prototypes*/
t_camera	camera_prototype(void);
t_object	plane_prototype(void);
t_object	sphere_prototype(void);
t_object	cone_prototype(void);
t_object	cylinder_prototype(void);
t_light		light_prototype(void);
t_object	cube_prototype(void);

/* parse ppm*/
void	parse_ppm(t_world *world, t_parser *parser);

#endif
