/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:04:49 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:44:03 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Allocate (with malloc(3)) and returns a “fresh” string ending with ’\0’
representing the integer n given as argument.
Negative numbers must be supported. If the allocation fails,
the function returns NULL.*/

static int	ft_log_ten(long int x)
{
	int	log;

	log = 0;
	if (x < 0)
		x = x * -1;
	while (x >= 10)
	{
		x /= 10;
		log++;
	}
	return (log);
}

static char	*ft_convert_int(long int x, char *str, int *i, int len)
{
	if (x / 10 != 0)
	{
		ft_convert_int(x / 10, str, i, len);
	}
	str[*i] = (x % 10 + 48);
	(*i)++;
	return (str);
}

char	*ft_itoa(int n)
{
	int			i;
	int			len;
	char		*str;
	long int	x;

	x = n;
	i = 0;
	if (x < 0)
		len = ft_log_ten(x) + 2;
	else
		len = ft_log_ten(x) + 1;
	str = (char *)malloc(sizeof(*str) * len + 1);
	if (str != NULL)
	{
		if (x < 0)
		{
			str[i] = '-';
			x *= -1;
			i++;
		}
		str = ft_convert_int(x, str, &i, len);
		str[i] = '\0';
	}
	return (str);
}
