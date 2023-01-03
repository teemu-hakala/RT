#include "RT.h"

/*

The PPM file is built in 9 sections separated by white-spaces.
*/

typedef struct s_ppm_image
{
	int		height;
	int		width;
	int		max_value;
	t_tuple	**pixels;
}				t_ppm_image;

void	allocate_pixel_array(t_ppm_image *image)
{
	int i;
	i = 0;

	image->pixels = (t_tuple **)malloc(sizeof(t_tuple) * image->height);
	if (!image->pixels)
		handle_errors("unable to malloc for image pixels");
	while (i < image->height)
	{
		image->pixels[i] = (t_tuple *)malloc(sizeof(t_tuple) * image->width);
		if (!image->pixels[i])
		{
			ft_memdelarray((void**)image->pixels, i - 1);
			return ;
		}
		i++;
	}
}

void	parse_pixels(char **array, t_ppm_image *image, int length)
{
	int	h;
	int	w;
	int	i;
	int	j;

	h = 0;
	j = 4;
	allocate_pixel_array(image);
	while (h < image->height && j < length)
	{
		w = 0;
		while (w < image->width)
		{
			i = 0;
			image->pixels[h][w] = point(0, 0, 0);
			while (i < 3)
			{
				image->pixels[h][w].array[i] = \
					ft_atof(array[j++]) / image->max_value;
				i++;
			}
			w++;
		}
		h++;

	}
}

void	print_pixels(t_ppm_image *image)
{
	int x = 0;
	int y;

	while (x < image->height)
	{
		y = 0;
		while (y < image->width)
		{
			printf("x: %d, y: %d || %f %f %f\n", y, x, image->pixels[x][y].array[0],image->pixels[x][y].array[1], image->pixels[x][y].array[2]);
			y++;
		}
		x++;
	}
}

void	parse_ppm(t_world *world, t_parser *parser)
{
	t_ppm_image	image;
	char	**array;
	int	length;

	(void)world;
	array = ft_strsplit(parser->string, ' ');
	length = ft_count_words(parser->string, ' ');
	printf("length = %d\n", length);
	if ((length - 4) % 3 != 0)
		handle_errors("ppm parser error");
	if (strcmp("P3", array[0]) != 0)
		handle_errors("incorrect ppm type");
	image.width = ft_atoi(array[1]);
	image.height = ft_atoi(array[2]);
	image.max_value = ft_atoi(array[3]);
	allocate_pixel_array(&image);
	parse_pixels(array, &image, length);
	print_pixels(&image);
}
