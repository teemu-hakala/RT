/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:28:57 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/26 13:11:51 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

typedef struct s_comp
{
	t_fl		time;
	t_tuple		point;
	t_tuple		eyev;
	t_tuple		normalv;
}				t_comp;

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
}	t_world;

# endif