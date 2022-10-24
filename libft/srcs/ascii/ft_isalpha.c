/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:03:35 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:43:51 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_isalpha(int c)
{
	if (ft_isuppercase(c) || ft_islowercase(c) == 1)
		return (1);
	else
		return (0);
}
