









#ifndef MOTION_BLUR_H
# define MOTION_BLUR_H
# include "RT.h"
# define SHUTTER_TIME 1.0
# define SHUTTER_COUNT 13

typedef struct s_shutter_configuration
{
	t_fl		time;
	uint64_t	count;
}	t_shutter;

typedef struct s_movement
{
	// t_tuple		origin;
	t_tuple		velocity;
	double		time;
	bool		active;
}	t_movement;

#endif
