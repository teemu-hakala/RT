/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 10:01:40 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:46:47 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Sets every character of the string to the value ’\0*/

void	ft_strclr(char *s)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i])
		{
			s[i] = '\0';
			i++;
		}
	}
}
