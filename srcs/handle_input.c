/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:09:11 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 16:43:56 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
