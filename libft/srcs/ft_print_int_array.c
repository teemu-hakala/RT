/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 14:12:40 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:45:47 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_print_int_array(int **array, int y, int x)
{
	int	i;
	int	j;

	if (!array)
		return ;
	if (y == 0 || x == 0)
		return ;
	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			ft_putnbr(array[i][j]);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
