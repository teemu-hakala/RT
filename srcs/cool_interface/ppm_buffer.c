











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

void	ppm_push_string(char *string, uint64_t len)
{
	vec_push_arr(ppm_write_buffer(PPM_NON_ACTION, -1), string, len);
}
