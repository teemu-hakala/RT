/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:17:08 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/14 15:26:13 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include <mlx.h>
# include <stdint.h>
#include <stdio.h>
# include "libft.h"
# include "tuple.h"
# include "matrices.h"
# include "objects.h"

# define WIDTH 600
# define HEIGHT 400
# define KEY_DOWN 2
# define ESC 53
# define EPSILON 0.00001

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		length;
	int		endian;
}	t_img;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}			t_ray;

typedef struct s_intersect
{
	t_fl		time;
	t_object	*shape;
	int			hit;
}				t_intersect;


// need new name here
typedef struct s_intersections
{
	int num;
	t_intersect *intersections;

}				t_intersections;

typedef struct s_win
{
	t_img		img;
	void		*mlx;
	void		*win;
}	t_win;

/*tuple operations & matrix maths*/
t_tuple	point(t_fl x, t_fl y, t_fl z);
t_tuple	vector(t_fl x, t_fl y, t_fl z);
t_tuple	tuple_add(t_tuple *a, t_tuple *b);
t_tuple	tuple_sub(t_tuple *a, t_tuple *b);
t_tuple	tuple_multi(t_tuple *a, t_fl scalar);
t_tuple	tuple_div(t_tuple *a, t_fl scalar);
t_fl	magnitude(t_tuple *a);
t_tuple	normalize(t_tuple *a);
t_fl	dot_product(t_tuple *a, t_tuple *b);
t_tuple	cross_product(t_tuple *a, t_tuple *b);
int		matrix_comparison(t_fl **a, t_fl **b, uint32_t size);
t_fl	**matrix_multi_square(t_fl **a, t_fl **b, uint32_t size);
t_fl	*matrix_tuple_multi(t_fl **a, t_tuple tuple);
t_fl	**transpose_matrix(t_fl **a);
t_fl	**identity_matrix(void);
//t_mtx_4	*identity_matrix(t_mtx_4 *dst); // transform = identity_matrix(&(t_mtx_4){});
double	matrix_determinant(double **a);
t_fl	**submatrix(t_fl **a, uint32_t size, uint32_t row, uint32_t col);
t_fl	matrix_minors(t_fl **a, uint32_t row, uint32_t col, uint32_t size);
t_fl	matrix_cofactor(t_fl **a, uint32_t row, uint32_t col, uint32_t size);
t_fl	determinant(t_fl **a, uint32_t size);
t_fl	**matrix_inversion(t_fl **a, uint32_t size);

/* error handle*/
void	handle_errors(char *str);
void	free_win(t_win *win);

/* initialise */
void	initialise_window(t_win *win);

void	img_pixel_put(t_win *win, int x, int y, unsigned int colour);

/* handle input*/
int		handle_input(int key, t_win *win);

/* colour */
t_tuple	hex_to_argb(uint32_t colour);

/* object intialisation */
t_object sphere(t_tuple *origin, t_transform *transform, t_tuple *colour);

/* object intersection */
void	identify_hit(t_intersections *array);
void	sphere_intersection(t_ray *ray, t_object *shape, t_intersections *array);

/* testing */
void	ft_print_num_array(t_fl **array, int y, int x);



#endif
