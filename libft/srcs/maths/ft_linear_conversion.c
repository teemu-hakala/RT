/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linear_conversion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:45:05 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:44:07 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

double	ft_linear_conversion(t_range old, t_range new, double x)
{
	double	old_range;
	double	new_range;
	double	temp;

	old_range = old.max - old.min;
	new_range = new.max - new.min;
	temp = (((x - old.min) * new_range) / old_range) + new.min;
	return (temp);
}
