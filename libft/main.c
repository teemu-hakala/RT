#include "libft.h"
#include "stdio.h"
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

int	ft_create_file(int bytes, int lines)
{
	int		new_file;
	int		old_file;
	int		read_ret;
	char	read_buf[bytes + 1];
	int		i = 0;

	new_file = open("test1.txt", O_RDWR | O_CREAT, 0666);
	old_file = open("lorem.txt", O_RDONLY);
	if (new_file < 0)
	{
		printf("unable to create file");
		return (-1);
	}
	if (old_file < 0)
	{
		printf("unable to open lorem\n");
		return (-1);
	}
	while (i < lines)
	{
		read_ret = read(old_file, read_buf, bytes);

		if (read_ret > 0)
		{
			read_buf[read_ret] = '\n';
			write(new_file, read_buf, bytes + 1);
		}
		i++;
	}
	close (new_file);
	close (old_file);
	return (1);
}

int	main(int argc, char **argv)
{
	int			fd;
	char		*line;
	ssize_t		ret;
	size_t		line_count;
	int			i;

	fd = 0;
	line_count = 0;
	i = 1;

	int bytes = 20;
	int lines = 10;

	ft_create_file(bytes, lines);

	if (argc == 1)
	{
		printf("\033[0;33mEnter a file name. Type \"exit\" to quit\n\033[m");
		do{
			line_count++;
			ret = GNL_read_ret(0, &line);
			if (strcmp(line, "exit") != 0)
				printf("ret %zd\tline_nbr[%zu]: %s\n", ret, line_count, line);
		}while (strcmp(line, "exit") != 0);
	}
	while (i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
		{
			printf("unable to open file\n");
			return (0);
		}
		printf("\033[0;35m\n[START] file name: %s\tfd:%d\n\033[m", argv[i], fd);
		do{
			line_count++;
			ret = get_next_line(fd, &line);
			if (ret == 1)
			{
			printf("ret %zd\tline_nbr[%zu]: %s\n", ret, line_count, line);
			free(line);
			}
		}while (ret == 1);
		line = 0;
		printf("ret %zd\tline_nbr[%zu]: %s\n", ret, line_count, line);
		printf("\033[0;32m[DONE] file: %s\n\033[m", argv[i]);
		close(fd);
		i++;
		if (i != argc)
			printf("\n");
		line_count = 0;
	}
	return (0);
}