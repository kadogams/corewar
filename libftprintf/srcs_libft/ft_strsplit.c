/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:49:47 by skadogam          #+#    #+#             */
/*   Updated: 2019/03/09 08:25:03 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countwords(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
		s++;
	}
	return (count);
}

static void		*delete_tab(char **tab, size_t n)
{
	while (n--)
		ft_strdel(&tab[n]);
	free(tab);
	tab = NULL;
	return (NULL);
}

char			**ft_strsplit(const char *s, char c)
{
	size_t	i;
	size_t	len;
	char	**dst;

	if (!s || !c || !(dst = (char**)malloc(sizeof(*dst) *
	(ft_countwords(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			len = 0;
			while (s[len] && (s[len] != c))
				len++;
			if (!(dst[i++] = ft_strsub(s, 0, len)))
				return (delete_tab(dst, i - 1));
			s += len;
		}
	}
	dst[i] = NULL;
	return (dst);
}
