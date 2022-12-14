










#include "RT.h"

static void	rect_pixel_put(t_img img, int y, int x, uint32_t colour)
{
	char	*pixel;

	pixel = img.addr + (y * img.length + x * (img.bpp / 8));
	*(uint32_t *)pixel = colour;
}

static t_rectangle	fit_rectangle_to_image_bounds(t_rectangle rect,
	t_rectangle image)
{
	if (rect.start.horizontal < image.start.horizontal)
		rect.start.horizontal = image.start.horizontal;
	if (rect.start.vertical < image.start.vertical)
		rect.start.vertical = image.start.vertical;
	if (rect.end.horizontal > image.end.horizontal)
		rect.end.horizontal = image.end.horizontal;
	if (rect.end.vertical > image.end.vertical)
		rect.end.vertical = image.end.vertical;
	return (rect);
}

void	put_rectangle_to_image(t_img img, t_rectangle image,
	t_rectangle rect, t_tuple colour)
{
	uint32_t	colour_hex;
	t_canvas	point;

	colour_hex = clamped_rgba_to_hex(&colour.tuple.colour);
	rect = fit_rectangle_to_image_bounds(rect, image);
	point.vertical = rect.start.vertical;
	while (point.vertical < rect.end.vertical)
	{
		point.horizontal = rect.start.horizontal;
		while (point.horizontal < rect.end.horizontal)
		{
			rect_pixel_put(img, point.vertical, point.horizontal, colour_hex);
			point.horizontal++;
		}
		point.vertical++;
	}
}

void	progress_bar(t_img img, t_fl progress_percentage, t_fl prev_perc)
{
	t_rectangle	image_bounds;
	t_rectangle	rectangle;
	t_tuple		colour;

	image_bounds = (t_rectangle){.start = {.horizontal = (WIDTH - 20) * \
		prev_perc, .vertical = 0}, \
		.end = {.horizontal = WIDTH - 20, .vertical = 20}};
	rectangle = (t_rectangle){.start = {.horizontal = progress_percentage, \
		.vertical = 0}, \
		.end = {.horizontal = (WIDTH - 20) * progress_percentage + 10, \
		.vertical = 20}};
	if (prev_perc == 0)
		rectangle.start.horizontal = 0;
	colour = (t_tuple){.tuple.colour = {.r = progress_percentage, \
		.g = progress_percentage, .b = 1, .a = 0}};
	put_rectangle_to_image(img, image_bounds, rectangle, colour);
	prev_perc = progress_percentage;
}
