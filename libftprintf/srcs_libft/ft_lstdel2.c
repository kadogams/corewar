/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:50:36 by skadogam          #+#    #+#             */
/*   Updated: 2018/11/15 15:50:39 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel2(t_list **alst)
{
	t_list	*tmp;

	if (!alst)
		return ;
	while (*alst)
	{
		tmp = (*alst)->next;
		free((*alst)->content);
		(*alst)->content = NULL;
		(*alst)->content_size = 0;
		free(*alst);
		*alst = NULL;
		*alst = tmp;
	}
}
