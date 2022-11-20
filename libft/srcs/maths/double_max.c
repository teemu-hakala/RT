/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_max.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:28:22 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/18 17:01:43 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	double_max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
