/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stderror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:12:10 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:46:29 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Outputs the string s to the standard error followed by a ’\n’.*/

void	ft_stderror(char const *s)
{
	if (!s)
		return ;
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
}
