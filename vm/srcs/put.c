/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:30:34 by skadogam          #+#    #+#             */
/*   Updated: 2019/02/21 17:31:47 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	put_neutral(int n)
{
	ft_printf("%.2x ", n);
}

void	put_red(int n)
{
	ft_printf("\x1B[31m%.2x\x1b[0m ", n);
}

void	put_blue(int n)
{
	ft_printf("\x1B[34m%.2x\x1b[0m ", n);
}

void	put_green(int n)
{
	ft_printf("\x1B[32m%.2x\x1b[0m ", n);
}

void	put_yellow(int n)
{
	ft_printf("\x1B[33m%.2x\x1b[0m ", n);
}
