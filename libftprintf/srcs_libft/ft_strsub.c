/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 11:25:23 by skadogam          #+#    #+#             */
/*   Updated: 2018/07/04 15:28:41 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dst;

	if (len == 0)
		return (ft_strnew(0));
	if (!s || !s[start] || !s[start + len - 1] || !(dst = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (i < len)
		dst[i++] = s[start++];
	dst[i] = '\0';
	return (dst);
}
