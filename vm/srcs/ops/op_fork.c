/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:58:21 by skadogam          #+#    #+#             */
/*   Updated: 2019/03/06 17:41:52 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** FORK
** arg: {T_DIR}
** crée un nouveau processus, qui hérite des diﬀérents états de son père,
** à part son PC, qui est mis à (PC + (1er paramètre % IDX_MOD))
*/

int		op_fork(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3])
{
	if (arg_type[0] == DIR_CODE)
	{
		if (vm->opt_v & 4)
			verbosity_4(*pc, g_op[12], pc->arg, pc->arg_type);
		if (vm->opt_v & 16)
			verbosity_16(*pc, vm->arena, pc->index,
				pc->index + pc->arg_len + 1);
		if (init_pc(vm, pc->champi, pc->index + arg[0] % IDX_MOD) == KO)
			return (KO);
		pc_copy(vm->pc, pc);
		pc->champi->nb_process++;
		vm->nb_process++;
	}
	pc->index += pc->arg_len + 1;
	return (OK);
}
