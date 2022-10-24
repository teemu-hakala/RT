/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:44:37 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:45:54 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Outputs the char c to the file descriptor fd.*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
