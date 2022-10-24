/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:31:46 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:45:44 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_print_array(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
		ft_putendl(array[i++]);
}
