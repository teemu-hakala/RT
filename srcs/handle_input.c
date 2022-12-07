











#include "RTv1.h"

void	esc_program(void)
{
	exit(EXIT_SUCCESS);
}

//should we add the press x to exit to this as well?

int	handle_input(int key)
{
	if (key == ESC)
		esc_program();
	return (0);
}
