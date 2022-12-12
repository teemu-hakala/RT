
#ifndef PATTERNS_H
# define PATTERNS_H
# include "RT.h"

typedef enum e_pattern_type
{
	PATTERN_NONE = 0,
	PATTERN_VERTICAL_STRIPES = 1,
	PATTERN_HORIZONTAL_STRIPES = 2,
	PATTERN_CHECKERED = 3,
	PATTERN_CIRCLES = 4,
	PATTERN_GRADIENT = 5
}	t_type;

#endif