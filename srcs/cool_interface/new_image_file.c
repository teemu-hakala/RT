/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_image_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:20:30 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/11 17:49:20 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

int	get_new_file_for_image(void)
{
	static const char	*template = \
		"screenshots/screenshot_"
		"XXXXXXXXXXXXX"
		PPM_SUFFIX;
	char				*result_name;
	int					file_descriptor;

	result_name = ft_strdup(template);
	mkdir("screenshots", 0777);
	file_descriptor = mkstemps(result_name, sizeof(PPM_SUFFIX) - 1);
	free(result_name);
	if (file_descriptor < 0)
		handle_errors("mkstemps returned < 0");
	return (file_descriptor);
}

void	buffer_ppm_image_header(t_win *win, int max_value)
{
	char	*dimension;

	ppm_write_buffer(PPM_NEW_IMAGE, -1);
	ppm_push_string(PPM_MAGIC_NUMERAL, sizeof(PPM_MAGIC_NUMERAL) - 1);
	ppm_push_string(" ", sizeof(" ") - 1);
	dimension = ft_itoa((int)win->img.dimensions.canvas.horizontal);
	ppm_push_string(dimension, ft_strlen(dimension));
	free(dimension);
	ppm_push_string(" ", sizeof(" ") - 1);
	dimension = ft_itoa((int)win->img.dimensions.canvas.vertical);
	ppm_push_string(dimension, ft_strlen(dimension));
	free(dimension);
	ppm_push_string(" ", sizeof(" ") - 1);
	dimension = ft_itoa(max_value);
	ppm_push_string(dimension, ft_strlen(dimension));
	free(dimension);
	ppm_push_string("\n", sizeof("\n") - 1);
}
