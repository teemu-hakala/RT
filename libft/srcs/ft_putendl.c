/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:26:31 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:46:04 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Outputs the string s to the standard output followed by a ’\n’.*/

void	ft_putendl(char const *s)
{
	if (!s)
		return ;
	ft_putstr(s);
	ft_putstr("\n");
}
