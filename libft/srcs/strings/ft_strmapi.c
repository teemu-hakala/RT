/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:17:15 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:48:02 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Applies the function f to each character of the string passed as argument
by giving its index as first argument to create a “fresh”
new string (with malloc(3)) resulting from the successive applications of f*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*newstr;

	i = 0;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	newstr = (char *)malloc(sizeof(*newstr) * (len + 1));
	if (newstr != NULL)
	{
		while (s[i])
		{
			newstr[i] = f(i, s[i]);
			i++;
		}
		newstr[i] = '\0';
	}
	return (newstr);
}
