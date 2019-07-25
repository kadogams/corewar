/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 15:44:57 by skadogam          #+#    #+#             */
/*   Updated: 2018/09/12 15:07:32 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset_back(void *b, int c, size_t len, size_t n)
{
	while (n--)
		((unsigned char*)b)[--len] = (unsigned char)c;
	return (b);
}
