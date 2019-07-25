/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:40:11 by skadogam          #+#    #+#             */
/*   Updated: 2018/11/13 13:40:34 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstnew(void)
{
	t_dlist	*new;

	if (!(new = (t_dlist*)malloc(sizeof(*new))))
		return (NULL);
	new->content = NULL;
	new->previous = new;
	new->next = new;
	return (new);
}
