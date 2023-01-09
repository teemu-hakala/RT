#include "RT.h"

/*

The PPM file is built in 9 sections separated by white-spaces.
*/


void	allocate_pixel_array(t_ppm_image *image)
{
	int	i;

	i = 0;
	image->pixels = (t_tuple **)malloc(sizeof(t_tuple) * image->height);
	if (!image->pixels)
		handle_errors("unable to malloc for image pixels");
	while (i < image->height)
	{
		image->pixels[i] = (t_tuple *)malloc(sizeof(t_tuple) * image->width);
		if (!image->pixels[i])
		{
			ft_memdelarray((void **)image->pixels, i - 1);
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

void	parse_ppm(t_ppm_image *image, char *str)
{
	char		**array;
	int			length;

	array = ft_strsplit(str, ' ');
	length = ft_count_words(str, ' ');
	if ((length - 4) % 3 != 0)
		handle_errors("ppm parser error");
	if (strcmp("P3", array[0]) != 0)
		handle_errors("incorrect ppm type");
	image->width = ft_atoi(array[1]);
	image->height = ft_atoi(array[2]);
	image->max_value = ft_atoi(array[3]);
	allocate_pixel_array(image);
	parse_pixels(array, image, length);
}

void	open_ppm(t_ppm_image *image)
{
	t_vec	ppm_string_vec;
	char	*str;

	image->fd = open(image->name, O_RDONLY);
	if (image->fd < 0)
		handle_errors("unable to open ppm");
	read_ppm_contents(&ppm_string_vec, image->fd);
	str = (char *)ppm_string_vec.memory;
	parse_ppm(image, str);
	free(str);
}
