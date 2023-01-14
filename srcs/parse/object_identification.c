











#include "RT.h"

uint64_t	object_identification(void)
{
	static uint64_t	object_id = 0;

	return (object_id++);
}
