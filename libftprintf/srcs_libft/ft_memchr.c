/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 11:17:45 by skadogam          #+#    #+#             */
/*   Updated: 2018/06/26 14:24:59 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*cs;

	cs = (const unsigned char*)s;
	while (n--)
	{
		if (*cs == (unsigned char)c)
			return ((void*)cs);
		cs++;
	}
	return (NULL);
}
