/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_overflow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:28:30 by thakala           #+#    #+#             */
/*   Updated: 2022/11/15 14:45:35 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

uint64_t	check_addition_overflow(uint64_t a, uint64_t b)
{
	if ((a >> 1) + (b >> 1) >= (uint64_t)(-1 - (a & 0x1U) - (b & 0x1U)) >> 1)
		return ((uint64_t)(-1));
	return (a + b);
}

uint64_t	check_multiplication_overflow(
	uint64_t multiplicand,
	uint64_t multiplier
)
{
	uint64_t	product;

	product = multiplicand * multiplier;
	if (multiplier == 0 || product / multiplier != multiplicand)
		return ((uint64_t)(-1));
	return (product);
}
