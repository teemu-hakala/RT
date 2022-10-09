/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:17:08 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/09 17:05:07 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include "../libft/includes/libft.h"
# include "../minilibx/mlx.h"

# define WIDTH 600
# define HEIGHT 400
# define KEY_DOWN 2
# define ESC 53

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}			t_tuple;

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

/*tuple operations*/
t_tuple	point(double x, double y, double z);
t_tuple	vector(double x, double y, double z);
t_tuple	tuple_add(t_tuple a, t_tuple b);
t_tuple	tuple_sub(t_tuple a, t_tuple b);
t_tuple	tuple_multi(t_tuple a, double scalar);
t_tuple	tuple_div(t_tuple a, double scalar);
double	magnitude(t_tuple a);
t_tuple	normalize(t_tuple a);
double	dot_product(t_tuple a, t_tuple b);
t_tuple	cross_product(t_tuple a, t_tuple b);

/* error handle*/
void	handle_errors(t_win	*win);
void	free_win(t_win *win);

/* initilise */
void	initialise_window(t_win *win);

void	img_pixel_put(t_win *win, int x, int y, int colour);

/* handle input*/
int	handle_input(int key, t_win *win);





#endif