/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:28:57 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/26 17:04:40 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

/*inside == true if hit occurs inside object, false otherwise. If hit occurs
iside object, normal vector is inverted*/

typedef struct s_intersect
{
	t_fl		time;
	t_object	*shape;
	int			hit;
}				t_intersect;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}			t_ray;

typedef struct s_world
{
	t_camera	camera;
	t_vec		lights;
	t_vec		objects;
	t_vec		intersections;
	t_vec		hits;
	t_ray		ray;
	uint64_t	object_index;
}	t_world;

# endif