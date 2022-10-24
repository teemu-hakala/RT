/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:11:37 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 15:27:56 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Iterates the list lst and applies the function f to each link.*/

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
		f(lst);
		lst = lst->next;
	}
}
