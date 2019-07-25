/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:39:59 by skadogam          #+#    #+#             */
/*   Updated: 2018/11/13 13:40:01 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdelone(t_dlist **alst)
{
	t_dlist	*tmp;

	if (!alst || !*alst)
		return ;
	else if (*alst != (*alst)->next)
		tmp = (*alst)->next;
	else
		tmp = NULL;
	if ((*alst)->previous)
		(*alst)->previous->next = (*alst)->next;
	if ((*alst)->next)
		(*alst)->next->previous = (*alst)->previous;
	free((*alst)->content);
	(*alst)->content = NULL;
	free(*alst);
	*alst = NULL;
	*alst = tmp;
}
