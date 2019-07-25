/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 11:39:03 by skadogam          #+#    #+#             */
/*   Updated: 2018/11/16 11:39:06 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone2(t_list **alst)
{
	if (!alst || !*alst)
		return ;
	free((*alst)->content);
	(*alst)->content = NULL;
	(*alst)->content_size = 0;
	free(*alst);
	*alst = NULL;
}
