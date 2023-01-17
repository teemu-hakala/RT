#ifndef GROUPS_H
# define GROUPS_H

# include "RT.h"

typedef struct s_group
{
	t_vec		objects;
	t_transform	transform;
	//t_material	material;
}				t_group;

#endif