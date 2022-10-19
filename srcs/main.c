/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:02:35 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/19 10:38:35 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RTv1.h"

void test_new_ray(void)
{
	t_ray	ray;
	t_tuple	transform;
	t_ray	new;

	ray.origin.tuple.units = (t_units){1.0, 2.0, 3.0, 1.0};
	ray.direction.tuple.units = (t_units){0.0, 1.0, 0.0, 0.0};
	transform.tuple.units = (t_units){3.0, 4.0, 5.0, 1.0};
	new = ray_translation(ray, transform);
	printf("translated: \norigin: {%f, %f, %f}\ndirection: {%f, %f, %f}\n", new.origin.tuple.units.x, new.origin.tuple.units.y, new.origin.tuple.units.z, new.direction.tuple.units.x, new.direction.tuple.units.y, new.direction.tuple.units.z);
	new = ray_scale(ray, transform);
	printf("translated: \norigin: {%f, %f, %f}\ndirection: {%f, %f, %f}\n", new.origin.tuple.units.x, new.origin.tuple.units.y, new.origin.tuple.units.z, new.direction.tuple.units.x, new.direction.tuple.units.y, new.direction.tuple.units.z);
}


void	ft_print_mtx(t_mtx *mtx)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%.1f, ", mtx->array[4 * i + j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	test_matrix_inversion(void)
{
	t_mtx	mtx;
	t_mtx	transformation;

	mtx.tuple_rows[0] = (t_quad_tuple){1.0, 2.0, 1.0, 1.0};
	mtx.tuple_rows[1] = (t_quad_tuple){0.0, 1.0, 0.0, 1.0};
	mtx.tuple_rows[2] = (t_quad_tuple){2.0, 3.0, 4.0, 1.0};
	mtx.tuple_rows[3] = (t_quad_tuple){1.0, 1.0, 1.0, 1.0};

	transformation.tuple_rows[0] = (t_quad_tuple){2.0, 5.0, 1.0, 1.0};
	transformation.tuple_rows[1] = (t_quad_tuple){6.0, 7.0, 1.0, 1.0};
	transformation.tuple_rows[2] = (t_quad_tuple){1.0, 8.0, 1.0, 1.0};
	transformation.tuple_rows[3] = (t_quad_tuple){1.0, 1.0, 1.0, 1.0};

	printf("ORIGINAL mtx:\n");
	ft_print_mtx (&mtx);
	// printf("\nTRANSFORMED mtx\n");
	// matrix_multi_square (&mtx, &transformation, 4);
	// ft_print_mtx (&mtx);
	printf("\nINVERTED mtx\n");
	matrix_inversion (&mtx, 4);
	ft_print_mtx (&mtx);
	printf("\nRE-INVERTED, ORIGINAL, mtx\n");
	matrix_inversion (&mtx, 4);
	ft_print_mtx (&mtx);
}

t_object	sphere(t_tuple *origin, t_transform *transform, t_tuple *colour)
{
	return ((t_object)
		{
			.object.sphere = (t_sphere)
			{
				.origin = (t_tuple)
				{
					.tuple.units = (t_units)
					{
						origin->tuple.units.x,
						origin->tuple.units.y,
						origin->tuple.units.z,
						origin->tuple.units.w
					}
				},
				.transform = (t_transform)
				{
					.matrix = (t_tf_mtx)
					{
						.resultant = identity_matrix(),
						.inverse = identity_matrix()
					},
					.translation = transform->translation,
					.rotation = transform->rotation,
					.scale = transform->scale
				},
				.colour = (t_tuple)
				{
					.tuple.colour = (t_colour)
					{
						colour->tuple.colour.a,
						colour->tuple.colour.r,
						colour->tuple.colour.g,
						colour->tuple.colour.b
					}
				}
			},
			.type = OBJECT_SPHERE
		}
	);
}

void	test_red_disc(void)
{
	t_object	object_sphere;
	t_tuple		red;
	t_transform	transform;
	t_win		win;

	transform = (t_transform)
	{
		.translation = (t_tuple)
		{
			.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1 }
		},
		.rotation = (t_tuple)
		{
			.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1 }
		},
		.scale = (t_tuple)
		{
			.tuple.units = (t_units){ 1.0, 1.0, 1.0, POINT_1 }
		}
	};
	red = hex_to_argb(0xFF0000);
	object_sphere = sphere(
			&(t_tuple){.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1}},
			&transform,
			&red
		);
	initialise_window(&win);
	plot_points(&win, &object_sphere);
	mlx_hook(win.win, KEY_DOWN, 0, handle_input, &win);
	mlx_loop(win.mlx);
}

int	main(void)
{
	//test_matrix_inversion();
	test_red_disc();
	return (0);
}