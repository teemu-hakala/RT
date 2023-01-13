











#include "RT.h"

int	get_new_file_for_image(void)
{
	static const char	*template =
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
