/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:39:52 by skadogam          #+#    #+#             */
/*   Updated: 2018/11/13 13:39:54 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdel(t_dlist **alst)
{
	t_dlist	*tmp;

	if (!alst || !*alst)
		return ;
	(*alst)->previous->next = NULL;
	while (*alst)
	{
		tmp = (*alst)->next;
		free((*alst)->content);
		(*alst)->content = NULL;
		free(*alst);
		*alst = NULL;
		*alst = tmp;
	}
}
