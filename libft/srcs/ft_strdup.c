/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:22:15 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:48:02 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* The ft_strdup() function allocates sufficient memory for a copy of the string
s1, does the copy, and returns a pointer to it.  The pointer may
subsequently be used as an argument to the function free(3).*/

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*str;

	len = ft_strlen(s1) + 1;
	i = 0;
	str = (char *) malloc(sizeof(char) * len);
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
