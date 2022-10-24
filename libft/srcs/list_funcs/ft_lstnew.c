/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 21:30:25 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 15:28:01 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Allocates (with malloc(3)) and returns a “fresh” link. The variables content
and content_size of the new link are initialized by copy of the parameters
of the function. If the parameter content is nul, the variable content is
initialized to NULL and the variable content_size is initialized to 0
even if the parameter content_size isn’t. The variable next is initialized
to NULL. If the allocation fails, the function returns NULL.*/

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*new_node;

	new_node = (t_list *)malloc(sizeof(*new_node));
	if (new_node)
	{
		if (content != NULL)
		{
			new_node->content = (void *)malloc(sizeof(*content) * content_size);
			if (new_node->content == NULL)
			{
				free(new_node);
				return (NULL);
			}
			ft_memcpy (new_node->content, content, content_size);
			new_node->content_size = content_size;
		}
		else
		{
			new_node->content = NULL;
			new_node->content_size = 0;
		}
		new_node->next = NULL;
		return (new_node);
	}
	return (new_node);
}
