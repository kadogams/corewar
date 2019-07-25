/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 20:51:05 by adefonta          #+#    #+#             */
/*   Updated: 2019/02/20 14:16:50 by adefonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "visu.h"

int		coord_to_pos(int x, int y, int width)
{
	return ((int)(x + y * width));
}

char	*ft_strjoin_free(char *s1, char *s2, int i_free)
{
	char	*join;
	size_t	len;
	size_t	i;
	size_t	start;

	join = NULL;
	i = -1;
	if (!s1 || !s2)
		return (NULL);
	start = ft_strlen(s1);
	len = start + ft_strlen(s2);
	if (!(join = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strcpy(join, s1);
	while (++i + start < len)
		join[start + i] = s2[i];
	join[len] = '\0';
	if (i_free > 1 || i_free == 0)
		free(s1);
	if (i_free > 1 || i_free == 1)
		free(s2);
	return (join);
}

char	*strint(char *base, int data)
{
	char	*s_data;

	if (!(s_data = ft_itoa(data)))
		return (NULL);
	return (ft_strjoin_free(base, s_data, 1));
}

void	ft_bzero_double(double *s, size_t n)
{
	while (n--)
		s[n] = 0;
}
