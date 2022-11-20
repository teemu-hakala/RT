/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_min.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:27:54 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/18 17:01:09 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	double_min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
