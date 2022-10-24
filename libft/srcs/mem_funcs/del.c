/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:43:38 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:42:45 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	del(void *content, size_t content_size)
{
	(void) content_size;
	if (content)
	{
		free(content);
		content = NULL;
	}
}
