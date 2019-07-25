/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:41:43 by skadogam          #+#    #+#             */
/*   Updated: 2019/03/06 17:41:56 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** LOAD
** arg: {T_DIR | T_IND, T_REG}
** charge la valeur du 1er param dans le registre
*/

int		op_ld(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3])
{
	pc->carry = 0;
	if (arg_type[0] != REG_CODE && arg_type[1] == REG_CODE)
	{
		if (vm->opt_v & 4)
			verbosity_4(*pc, g_op[2], pc->arg, pc->arg_type);
		if (vm->opt_v & 16)
			verbosity_16(*pc, vm->arena, pc->index,
				pc->index + pc->arg_len + 1);
		if (pc->arg_type[0] == IND_CODE)
			pc->reg[arg[1]] = arg_read(vm->arena,
				pc->index + (arg[0] % IDX_MOD), REG_SIZE);
		else
			pc->reg[arg[1]] = arg[0];
		if (!pc->reg[arg[1]])
			pc->carry = 1;
	}
	pc->index += pc->arg_len + 1;
	return (OK);
}
