/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:50:55 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:48:02 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Applies the function f to each character of the string given as argument
to create a “fresh” new string (with malloc(3))
resulting from the successive applications of f.*/

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	i;
	char			*newstr;
	int				len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	newstr = (char *)malloc(sizeof(*newstr) * (len + 1));
	i = 0;
	if (newstr != NULL)
	{
		while (s[i])
		{
			newstr[i] = f(s[i]);
			i++;
		}
		newstr[i] = '\0';
	}
	return (newstr);
}
