/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoimax_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:36:11 by skadogam          #+#    #+#             */
/*   Updated: 2018/10/04 13:48:59 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_base(char c, int base)
{
	if (base < 2 || base > 16)
		return (0);
	else if (c >= '0' && c <= '9' && base > c - '0')
		return (1);
	else if (c >= 'a' && c <= 'f' && base > c - 'a' + 10)
		return (2);
	else if (c >= 'A' && c <= 'F' && base > c - 'A' + 10)
		return (3);
	else
		return (0);
}

intmax_t	ft_atoimax_base(const char *str, int base)
{
	int				i;
	int				check;
	intmax_t		neg;
	intmax_t		res;

	i = 0;
	neg = 1;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' && base == 10)
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((check = ft_check_base(str[i], base)))
	{
		if (check == 1)
			res = res * base + str[i] - '0';
		else if (check == 2)
			res = res * base + str[i] - 'a' + 10;
		else
			res = res * base + str[i] - 'A' + 10;
		i++;
	}
	return (res * neg);
}
