/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:50:11 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:48:02 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	char	c;
	int		len;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	while (i < len / 2)
	{
		c = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = c;
		i++;
	}
	return (str);
}
