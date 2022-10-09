/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:16:31 by deelliot          #+#    #+#             */
/*   Updated: 2022/02/18 13:40:54 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int	result;
	int	sub;
	int	increment;

	if (nb < 0 || !nb)
		return (0);
	result = nb;
	sub = 1;
	increment = 0;
	while (result > 0)
	{
		result = result - sub;
		sub = sub + 2;
		increment = increment + 1;
	}
	if (result < 0)
		return (0);
	return (increment);
}
