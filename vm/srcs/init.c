/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:14:34 by adefonta          #+#    #+#             */
/*   Updated: 2019/03/09 09:09:17 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_vm(t_vm *vm)
{
	ft_bzero(vm, sizeof(t_vm));
	vm->opt_v = 1;
	vm->opt_dump = -1;
}

int		init_pc(t_vm *vm, t_champi *champi, unsigned int index)
{
	t_pc	*pc;

	if (!(pc = (t_pc *)ft_memalloc(sizeof(t_pc))))
		return (error_int(ERROR_PC_NULL));
	pc->index = index % MEM_SIZE;
	pc->carry = 0;
	pc->champi = champi;
	pc->reg[1] = champi->number;
	if (!(vm->pc))
		vm->pc = pc;
	else
	{
		pc->next = vm->pc;
		vm->pc = pc;
	}
	pc->nb = ++vm->tot_process;
	return (OK);
}
