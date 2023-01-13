











#include "RT.h"

t_vec	*ppm_write_buffer(uint8_t flag, int fd)
{
	static t_vec	write_buffer;

	if (write_buffer.memory == NULL)
		vec_new(&write_buffer, PPM_BUFFER_SIZE, sizeof(char));
	if (flag & PPM_NEW_IMAGE)
		vec_clear(&write_buffer);
	else if (flag & PPM_OUTPUT_IMAGE_DATA)
		write(fd, write_buffer.memory, write_buffer.len);
	return (&write_buffer);
}

void	write_ppm_pixel_max_255(uint32_t pixel)
{
	uint8_t		*pixel_chars;
	uint8_t		channel;
	char		result;

	pixel_chars = (uint8_t *)&pixel;
	channel = 4;
	while (channel-- > 0)
	{
		result = (char)pixel_chars[channel];
		vec_push_arr(ppm_write_buffer(PPM_NON_ACTION, -1), \
			&result, 1);
	}
}

void	write_ppm_from(t_win *win)
{
	const uint32_t	*pixel_argb	= (uint32_t *)win->img.addr;
	const uint64_t	pixel_count = win->img.dimensions.canvas.horizontal \
		* win->img.dimensions.canvas.vertical;
	uint64_t		p;
	int				image_file_descriptor;

	image_file_descriptor = get_new_file_for_image();
	p = 0;
	vec_push_arr(ppm_write_buffer(PPM_NEW_IMAGE, -1), "P6", 2);

	while (p < pixel_count)
	{
		write_ppm_pixel_max_255(pixel_argb[p]);
		p++;
	}
	ppm_write_buffer(PPM_OUTPUT_IMAGE_DATA, image_file_descriptor);
	close(image_file_descriptor);
}

void	*watch_for_screenshot(void *param)
{
	t_win	*win;

	win = (t_win *)param;
	while (win->drawn == false)
		pthread_testcancel();
	write_ppm_from(win);
	return (NULL);

}

void	save_screenshot_once_drawn(t_win *win)
{
	static pthread_t	screenshot_thread;
	static int8_t		first = true;

	if (first == false)
		pthread_cancel(screenshot_thread);
	pthread_create(&screenshot_thread, NULL, watch_for_screenshot, &win);
	if (first == true)
		first = false;
}
