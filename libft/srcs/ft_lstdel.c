/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 20:25:47 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 15:27:52 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Takes as a parameter the adress of a pointer to a link and frees the memory
of this link and every successors of that link using the functions
del and free(3). Finally the pointer to the link that was just freed
must be set to NULL*/

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*temp;

	while ((*alst) != NULL)
	{
		temp = *alst;
		*alst = temp->next;
		del (temp->content, temp->content_size);
		free(*alst);
		*alst = NULL;
	}
}
