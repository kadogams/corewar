/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:59:17 by skadogam          #+#    #+#             */
/*   Updated: 2019/03/06 17:42:09 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** LONG FORK
** arg: {T_DIR}
** similaire a fork sans le % IDX_MOD
*/

int		op_lfork(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3])
{
	if (arg_type[0] == DIR_CODE)
	{
		if (vm->opt_v & 4)
			verbosity_4(*pc, g_op[15], pc->arg, pc->arg_type);
		if (vm->opt_v & 16)
			verbosity_16(*pc, vm->arena, pc->index,
				pc->index + pc->arg_len + 1);
		if (init_pc(vm, pc->champi, pc->index - 1 + arg[0]) == KO)
			return (KO);
		pc_copy(vm->pc, pc);
		pc->champi->nb_process++;
		vm->nb_process++;
	}
	pc->index += pc->arg_len + 1;
	return (OK);
}
