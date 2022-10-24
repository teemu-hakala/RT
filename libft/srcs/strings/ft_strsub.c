/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:19:58 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:48:02 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*Allocates (with malloc(3)) and returns a “fresh” substring from the string
given as argument. The substring begins at indexstart and is of size len.
If start and len aren’t refering to a valid substring,the behavior
is undefined. If the allocation fails, the function returns NULL*/

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*newstr;

	if (!s)
		return (NULL);
	i = 0;
	newstr = (char *)malloc(sizeof(*newstr) * (len + 1));
	if (newstr == NULL)
		return (NULL);
	while (len > 0)
	{
		newstr[i] = s[start + i];
		i++;
		len--;
	}
	newstr[i] = '\0';
	return (newstr);
}
