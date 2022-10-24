/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:12:01 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 15:27:54 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Takes as a parameter a link’s pointer address and frees the
memory of the link’s content using the function del given as
a parameter, then frees the link’s memory using free(3). The
memory of next must not be freed under any circumstance.
Finally, the pointer to the link that was just freed must be set to NULL*/

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	del((*alst)->content, (*alst)->content_size);
	free (*alst);
	*alst = NULL;
}
