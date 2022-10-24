/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:53:36 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:48:02 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_transfer_heap(const int fd, char **line, char **heap)
{
	int		i;
	char	*temp;

	i = 0;
	while (heap[fd][i] != '\n' && heap[fd][i] != '\0')
		i++;
	*line = ft_strsub(heap[fd], 0, i);
	if (heap[fd][i] == '\n')
	{
		temp = ft_strdup(heap[fd] + i + 1);
		free (heap[fd]);
		heap[fd] = temp;
		if (heap[fd][0] == '\0')
			ft_strdel(&heap[fd]);
	}
	else
		ft_strdel(&heap[fd]);
	return (1);
}

static int	ft_check_file(const int fd, char **line, int ret, char **heap)
{
	if (ret < 0)
		return (-1);
	if (ret == 0 && heap[fd] == NULL)
		return (0);
	else
		return (ft_transfer_heap(fd, line, heap));
}

int	ft_read_file(int ret, char **heap, char *buf, int fd)
{
	char	*temp;

	while (ret > 0)
	{
		buf[ret] = '\0';
		if (heap[fd] == NULL)
		{
			heap[fd] = ft_strdup(buf);
			if (heap[fd] == NULL)
				return (-1);
		}
		else
		{
			temp = ft_strjoin(heap[fd], buf);
			if (temp == NULL)
				return (-1);
			free (heap[fd]);
			heap[fd] = temp;
		}
		if (ft_strchr(heap[fd], '\n'))
			break ;
		ret = read(fd, buf, BUFF_SIZE);
	}
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	static char	*heap[MAX_FD + 1];
	int			ret;

	if (fd < 0 || !line || fd > MAX_FD)
		return (-1);
	*line = NULL;
	ret = read(fd, buf, BUFF_SIZE);
	if (ft_read_file(ret, heap, buf, fd) == -1)
		return (-1);
	return (ft_check_file (fd, line, ret, heap));
}
