/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp_zero.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:19:54 by skadogam          #+#    #+#             */
/*   Updated: 2019/03/06 10:25:23 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp_zero(const void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (n--)
	{
		if (((unsigned char*)s)[i] != 0)
			return (((unsigned char*)s)[i]);
		i++;
	}
	return (0);
}
