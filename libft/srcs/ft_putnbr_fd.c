/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:19:54 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:46:08 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	x;

	x = n;
	if (x < 0)
	{
		ft_putchar_fd('-', fd);
		x *= -1;
	}
	if (x / 10 != 0)
	{
		ft_putnbr_fd(x / 10, fd);
	}
	ft_putchar_fd(x % 10 + 48, fd);
}
