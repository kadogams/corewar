/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:36:59 by skadogam          #+#    #+#             */
/*   Updated: 2018/10/10 09:32:45 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	ft_sqrt(float x)
{
	float	res;
	float	sq;
	float	digit;

	if (x < 0)
		return (0);
	res = 1;
	digit = 1;
	while (digit * digit < x / digit)
		digit *= 10;
	while (digit > 0.001)
	{
		while (res)
		{
			sq = res * res;
			if (sq == x)
				return (res);
			else if (sq > x)
				break ;
			res += digit;
		}
		res -= digit;
		digit /= 10;
	}
	return (res);
}
