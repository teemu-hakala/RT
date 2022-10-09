/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:24:54 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:48:02 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*Allocates (with malloc(3)) and returns a copy of the string given
as argument without whitespaces at the beginning or at the end of the string
Will be considered as whitespaces the following characters
’ ’, ’\n’ and ’\t’. If s has no whitespaces at the beginning or at the end,
the function returns a copy of s.
If the allocation fails the function returns NULL.*/

char	*ft_strtrim(char const *s)
{
	unsigned int		beg;
	unsigned int		end;
	char				*newstr;

	if (s == NULL)
		return (NULL);
	beg = 0;
	end = ft_strlen(s) - 1;
	while (s[beg] == 32 || s[beg] == '\n' || s[beg] == '\t')
		beg++;
	if (beg == end + 1)
		return (ft_strdup(""));
	while (s[end] == 32 || s[end] == '\n' || s[end] == '\t')
		end--;
	newstr = ft_strsub(s, beg, end - beg + 1);
	return (newstr);
}
