/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:16:31 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:46:01 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Outputs the string s to the file descriptor fd followed by a ’\n’.*/

void	ft_putendl_fd(char const *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\n", fd);
}
