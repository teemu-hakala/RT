/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:02:35 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/18 16:22:24 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RTv1.h"

// int main(void)
// {
// 	t_win	win;

// 	initialise_window(&win);
// 	mlx_hook(win.win, KEY_DOWN, 0, handle_input, &win);
// 	mlx_loop(win.mlx);
// 	return (0);
// }

// void	test_three_matrix_a3(void)
// {
// 	double **a3;

// 	a3 = (double **)ft_memallocarray(3, 3);

// 	a3[0][0] = 1;
// 	a3[0][1] = 2;
// 	a3[0][2] = 6;

// 	a3[1][0] = -5;
// 	a3[1][1] = 8;
// 	a3[1][2] =-4;

// 	a3[2][0] = 2;
// 	a3[2][1] = 6;
// 	a3[2][2] = 4;

// 	double minor;
// 	double cofactor;
// 	double determinant;

// 	cofactor = matrix_cofactor(a3, 0, 0);
// 	printf("cofactor = %f\n", cofactor);
// 	cofactor = matrix_cofactor(a3, 0, 1);
// 	printf("cofactor = %f\n", cofactor);
// 	cofactor = matrix_cofactor(a3, 0, 2);
// 	printf("cofactor = %f\n", cofactor);
// 	minor = matrix_minors(a3, 0, 0);
// 	printf("minor: %f\n", minor);
// }

// void	test_matrix_tuple_multi_four_matrix(void)
// {
// 	double **a4;

// 	a4 = (double **)ft_memallocarray(4, 4);

// 	a4[0][0] = -6;
// 	a4[0][1] = 1;
// 	a4[0][2] = 1;
// 	a4[0][3] = 6;

// 	a4[1][0] = -8;
// 	a4[1][1] = 5;
// 	a4[1][2] =8;
// 	a4[1][3] = 6;

// 	a4[2][0] = -1;
// 	a4[2][1] = 0;
// 	a4[2][2] = 8;
// 	a4[2][3] = 2;

// 	a4[3][0] = -7;
// 	a4[3][1] = 1;
// 	a4[3][2] = -1;
// 	a4[3][3] = 1;
// }

// void	test_matrix_determinant(void)
// {

// }

// void	test_tuple_reading(void)
// {
// 	t_tuple tuple;

// 	tuple.tuple = (t_units){ 1, 3, 5, 0 };

// 	int i;
// 	i = 0;
// 	while (i < 4)
// 	{
// 		printf("%0.f, ", tuple.array[i]);
// 		i++;
// 	}
// }

// int main(void)
// {
// 	t_ray	ray;
// 	t_tuple	transform;
// 	t_ray	new;

// 	ray.origin.tuple.units = (t_units){1.0, 2.0, 3.0, 1.0};
// 	ray.direction.tuple.units = (t_units){0.0, 1.0, 0.0, 0.0};
// 	transform.tuple.units = (t_units){3.0, 4.0, 5.0, 1.0};
// 	new = ray_translation(ray, transform);
// 	printf("translated: \norigin: {%f, %f, %f}\ndirection: {%f, %f, %f}\n", new.origin.tuple.units.x, new.origin.tuple.units.y, new.origin.tuple.units.z, new.direction.tuple.units.x, new.direction.tuple.units.y, new.direction.tuple.units.z);
// 	new = ray_scale(ray, transform);
// 	printf("translated: \norigin: {%f, %f, %f}\ndirection: {%f, %f, %f}\n", new.origin.tuple.units.x, new.origin.tuple.units.y, new.origin.tuple.units.z, new.direction.tuple.units.x, new.direction.tuple.units.y, new.direction.tuple.units.z);
// 	return (0);
// }


void	ft_print_mtx_4(t_mtx_4 *mtx)
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

// int main(void)
// {
// 	t_mtx_4 mtx;
// 	t_mtx_4 transformation;


// 	mtx.tuple_rows[0] = (t_quad_tuple){1.0, 2.0, 1.0, 1.0};
// 	mtx.tuple_rows[1] = (t_quad_tuple){0.0, 1.0, 0.0, 1.0};
// 	mtx.tuple_rows[2] = (t_quad_tuple){2.0, 3.0, 4.0, 1.0};
// 	mtx.tuple_rows[3] = (t_quad_tuple){1.0, 1.0, 1.0, 1.0};

// 	transformation.tuple_rows[0] = (t_quad_tuple){2.0, 5.0, 1.0, 1.0};
// 	transformation.tuple_rows[1] = (t_quad_tuple){6.0, 7.0, 1.0, 1.0};
// 	transformation.tuple_rows[2] = (t_quad_tuple){1.0, 8.0, 1.0, 1.0};
// 	transformation.tuple_rows[3] = (t_quad_tuple){1.0, 1.0, 1.0, 1.0};

// 	printf("ORIGINAL mtx:\n");
// 	ft_print_mtx_4 (&mtx);
// 	// printf("\nTRANSFORMED mtx\n");
// 	// matrix_multi_square (&mtx, &transformation, 4);
// 	// ft_print_mtx_4 (&mtx);
// 	printf("\nINVERTED mtx\n");
// 	matrix_inversion (&mtx, 4);
// 	ft_print_mtx_4 (&mtx);
// 	printf("\nRE-INVERTED, ORIGINAL, mtx\n");
// 	matrix_inversion (&mtx, 4);
// 	ft_print_mtx_4 (&mtx);
// 	return (0);
// }

t_object sphere(t_tuple *origin, t_transform *transform, t_tuple *colour)
{
	return ((t_object)
	{
		.object.sphere = (t_sphere)
		{
			.origin = (t_tuple){.tuple.units = (t_units)
				{origin->tuple.units.x,
				origin->tuple.units.y,
				origin->tuple.units.z,
				origin->tuple.units.w}},
			.transform = (t_transform){transform->translation,
				transform->rotation,
				transform->scale},
			.colour = (t_tuple){.tuple.colour = (t_colour)
				{colour->tuple.colour.a,
				colour->tuple.colour.r,
				colour->tuple.colour.g,
				colour->tuple.colour.b}}
		},
		.type = OBJECT_SPHERE
	});
}

int main (void)
{
	t_object	object_sphere;
	t_tuple		red;
	t_transform	transform;
	t_win	win;

	transform =(t_transform)
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
	plot_points(&win, object_sphere);
	mlx_init();
	return (0);
}