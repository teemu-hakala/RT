/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:12:03 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/09 15:40:36 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_clear_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
			i++;
		else
			break ;
	}
	return (i);
}