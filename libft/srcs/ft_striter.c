/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 10:34:44 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:48:02 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Applies the function f to each character of the string passed as argument.
Each character is passed by address to f to be modified if necessary.*/

void	ft_striter(char *s, void (*f)(char *))
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i])
		{
			f(&s[i]);
			i++;
		}
	}
}
