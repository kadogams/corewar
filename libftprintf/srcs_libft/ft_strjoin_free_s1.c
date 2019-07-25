/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclecler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 18:44:08 by aclecler          #+#    #+#             */
/*   Updated: 2019/03/12 14:22:34 by dazheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_s1(char *s1, char const *s2)
{
	char	*join;
	size_t	len;
	size_t	i;
	size_t	start;

	join = NULL;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(join = (char*)malloc(sizeof(char) * (len + 1))))
	{
		ft_strdel(&s1);
		return (NULL);
	}
	ft_strcpy(join, s1);
	start = ft_strlen(s1);
	while (i + start < len)
	{
		join[start + i] = s2[i];
		i++;
	}
	ft_strdel(&s1);
	join[start + i] = '\0';
	return (join);
}
