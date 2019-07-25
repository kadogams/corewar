/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 21:44:34 by skadogam          #+#    #+#             */
/*   Updated: 2018/08/02 17:49:22 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*first;

	if (!lst || !f || !(new = ft_lstnew(lst->content, lst->content_size)))
		return (NULL);
	new = f(lst);
	first = new;
	lst = lst->next;
	while (lst)
	{
		if (!(new->next = ft_lstnew(lst->content, lst->content_size)))
			return (NULL);
		new->next = f(lst);
		new = new->next;
		lst = lst->next;
	}
	return (first);
}
