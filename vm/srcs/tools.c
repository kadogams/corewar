/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:34:28 by adefonta          #+#    #+#             */
/*   Updated: 2019/03/06 15:08:43 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	tools_memcpy_int(t_vm *vm, unsigned int index, int n)
{
	int	size;

	size = 4;
	while (size--)
	{
		vm->arena[(index + size) % MEM_SIZE] = (unsigned char)n;
		n >>= 8;
	}
}
