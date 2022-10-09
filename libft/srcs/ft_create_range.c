/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_range.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:49:43 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:43:40 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_range	ft_create_range(double min, double max)
{
	t_range	range;

	range.min = min;
	range.max = max;
	range.median = (max + min) / 2;
	return (range);
}
