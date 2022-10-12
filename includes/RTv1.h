/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:17:08 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/12 11:37:53 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include "../libft/includes/libft.h"
# include <mlx.h>
# include <stdint.h>
# include <stdio.h>
# include "tuple.h"

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
}				t_img;

typedef struct s_win
{
	t_img		img;
	void		*mlx;
	void		*win;
}				t_win;

/*tuple operations & matrix maths*/
t_tuple	point(double x, double y, double z);
t_tuple	vector(double x, double y, double z);
double	**tuple_to_array(t_tuple tuple);
t_tuple	tuple_add(t_tuple *a, t_tuple *b);
t_tuple	tuple_sub(t_tuple *a, t_tuple *b);
t_tuple	tuple_multi(t_tuple *a, double scalar);
t_tuple	tuple_div(t_tuple *a, double scalar);
double	magnitude(t_tuple *a);
t_tuple	normalize(t_tuple *a);
double	dot_product(t_tuple *a, t_tuple *b);
t_tuple	cross_product(t_tuple *a, t_tuple b);
int	matrix_comparison(double **a, double **b, int size);
double **matrix_multi_square(double **a, double **b, int size);
double *matrix_tuple_multi(double **a, t_tuple tuple);
double	**transpose_matrix(double **a);
double **identity_matrix(void);
double	matrix_determinant(double **a);
double	**submatrix(double **a, int size, int row, int col);
double matrix_minors(double **a, int row, int col, int size);
double matrix_cofactor(double **a, int row, int col, int size);
double determinant(double **a, int size);

/* error handle*/
void	handle_errors(t_win	*win);
void	free_win(t_win *win);

/* initilise */
void	initialise_window(t_win *win);

void	img_pixel_put(t_win *win, int x, int y, int colour);

/* handle input*/
int	handle_input(int key, t_win *win);

/* testing */
void	ft_print_num_array(double **array, int y, int x);



#endif