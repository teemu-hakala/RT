/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:52:10 by ikarjala          #+#    #+#             */
/*   Updated: 2023/02/15 19:17:25 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"


#if 0
/* Create pseudorandom direction vector
*/
static t_tuple	rand_vec(int x, int y)
{
	const unsigned	w = 8 * sizeof(unsigned);
	const unsigned	s = w / 2;
	double			rn;

	x *= 3284157443; y ^= (x << s) | (x >> (w-s));
	y *= 1911520717; x ^= (y << s) | (y >> (w-s));
	x *= 2048419325;
	rn = x * (M_PI / ~(~0u >> 1));
	return (vector (cos(rn), sin(rn), 0));
}

static t_fl	smooth_step (t_fl a, t_fl b, t_fl t)
{
	// for now just lerp
	return (a + t * (b - a));
}

void	perlin_at(t_pattern *pattern, t_tuple *point, t_tuple *colour)
{
	t_units	ext;
	t_fl	sample;
	
	(void)(pattern);
	ext.x = floor (point->tuple.units.x * 10.05);
	ext.y = floor (point->tuple.units.y * 10.05);
	ext.z = ext.x + 1.0;
	ext.w = ext.y + 1.0;

	sample = smooth_step (
		smooth_step (
			dot_product (tuple_sub (*point, vector(ext.x,ext.y,0)), rand_vec ((int)(ext.x), (int)(ext.y))),
			dot_product (tuple_sub (*point, vector(ext.z,ext.y,0)), rand_vec ((int)(ext.z), (int)(ext.y))),
			point->tuple.units.x),
		smooth_step (
			dot_product (tuple_sub (*point, vector(ext.x,ext.w,0)), rand_vec ((int)(ext.x), (int)(ext.w))),
			dot_product (tuple_sub (*point, vector(ext.z,ext.w,0)), rand_vec ((int)(ext.z), (int)(ext.w))),
			point->tuple.units.x),
		point->tuple.units.y);
	sample = sample * 0.5 + 0.5;
	//*colour = vector (1, 0, 0);
	//*colour = tuple_add (pattern->colour_a, vector (sample, sample, sample));
	*colour = vector (sample, sample, sample);
}
#else
void	perlin_at(t_pattern *pattern, t_tuple *point, t_tuple *colour)
{
	//(void)(point);
	if (point->tuple.units.x > -0.2 && point->tuple.units.x < 0.2 && 
		point->tuple.units.y > -0.2 && point->tuple.units.y < 0.2) 
		*colour = tuple_scale (pattern->colour_a, 1.0);
		//*colour = tuple_scale (pattern->colour_a, point->tuple.units.x + point->tuple.units.y);
	else
		*colour = vector (0, 0, 0);
}
#endif
