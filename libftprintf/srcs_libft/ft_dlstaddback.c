/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:39:40 by skadogam          #+#    #+#             */
/*   Updated: 2018/11/13 13:39:48 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstaddback(t_dlist **alst, t_dlist *new)
{
	if (!alst || !new)
		return ;
	else if (*alst)
	{
		new->next = *alst;
		new->previous = (*alst)->previous;
		(*alst)->previous->next = new;
		(*alst)->previous = new;
	}
	else
		*alst = new;
}
