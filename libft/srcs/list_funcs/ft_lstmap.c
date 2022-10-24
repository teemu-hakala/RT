/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:30:16 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 15:27:59 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Iterates a list lst and applies the function f to each link to create a
“fresh”list (using malloc(3)) resulting from the successive applications
of f. If the allocation fails, the function returns NULL.*/

static void	ft_clear_list(t_list **new_lst)
{
	t_list	*temp;

	while ((*new_lst) != NULL)
	{
		temp = *new_lst;
		*new_lst = temp->next;
		free (temp->content);
		free (temp);
		temp = NULL;
	}
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*temp;
	t_list	*new_lst;
	t_list	*new_ele;

	if (!lst || !f)
		return (NULL);
	new_lst = NULL;
	while (lst != NULL)
	{
		new_ele = NULL;
		temp = lst->next;
		new_ele = f(lst);
		if (new_ele == NULL)
		{
			ft_clear_list(&new_lst);
			return (NULL);
		}
		ft_lstadd_back (&new_lst, new_ele);
		lst = temp;
	}
	return (new_lst);
}
