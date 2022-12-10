
#ifndef PATTERNS_H
# define PATTERNS_H
# include "RT.h"

typedef enum e_pattern_type
{
	PATTERN_NONE = 0,
	PATTERN_STRIPE = 1,
	PATTERN_CHECKERED = 2,
	PATTERN_CIRCLES = 3,
	PATTERN_GRADIENT = 4
}	t_pattern_type;

typedef struct s_pattern_col
{
	t_tuple	a;
	t_tuple	b;
}				t_pattern_col;

#endif