/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:46:12 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:48:02 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Allocates (with malloc(3)) and returns a “fresh” string ending with ’\0’,
result of the concatenation of s1 and s2.
If the allocation fails the function returns NULL.*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*newstr;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (ft_strdup(""));
	len = ft_strlen(s1) + ft_strlen(s2);
	newstr = (char *)malloc(sizeof(*newstr) * (len + 1));
	if (newstr != NULL)
	{
		ft_strcpy(newstr, s1);
		ft_strcat(newstr, s2);
	}
	return (newstr);
}
