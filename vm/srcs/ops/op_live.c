/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:36:26 by skadogam          #+#    #+#             */
/*   Updated: 2019/07/13 10:41:30 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	verbosity_1(int nb, char *name)
{
	ft_printf("A process shows that player %d (%s) is alive\n", nb, name);
}

int			op_live(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3])
{
	int	i;

	if (arg_type[0] == DIR_CODE)
	{
		(vm->opt_v & 4) ? verbosity_4(*pc, g_op[1], pc->arg, pc->arg_type) : 0;
		if (vm->opt_v & 16)
			verbosity_16(*pc, vm->arena, pc->index,
						pc->index + pc->arg_len + 1);
		i = -1;
		while (++i < vm->nb_champi)
		{
			if (vm->champi[i]->number == arg[0])
			{
				if (vm->opt_v & 1)
					verbosity_1(pc->champi->number, vm->champi[i]->name);
				vm->champi[i]->nb_live++;
				vm->champi[i]->last_live = vm->tot_cycles;
				vm->last_living_champi = vm->champi[i];
			}
		}
		vm->live_calls++;
		pc->live = 1;
	}
	pc->index += pc->arg_len + 1;
	return (OK);
}
