/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_sqrt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:46:08 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:43:45 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_find_next_sqrt(int nb)
{
	int	res;
	int	i;
	int	sub;

	if (!nb || nb < 0)
		return (0);
	if (ft_sqrt(nb) != 0)
		nb += 1;
	res = nb;
	i = 0;
	sub = 1;
	while (res > 0)
	{
		res -= sub;
		sub += 2;
		i += 1;
	}
	if (res < 0)
		return (ft_sqrt(nb + (-res)));
	return (i);
}
