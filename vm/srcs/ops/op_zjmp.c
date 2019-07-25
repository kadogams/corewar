/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:52:23 by skadogam          #+#    #+#             */
/*   Updated: 2019/03/09 08:28:24 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** JUMP IF ZERO
** arg: {T_DIR}
** saute a l'adresse si le carry est a 1
*/

int		op_zjmp(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3])
{
	if (pc->carry && arg_type[0] == DIR_CODE)
	{
		if (vm->opt_v & 4)
			verbosity_4(*pc, g_op[9], pc->arg, pc->arg_type);
		pc->index += (unsigned int)(arg[0] % IDX_MOD);
	}
	else
		pc->index += pc->arg_len + 1;
	pc->index %= MEM_SIZE;
	return (OK);
}
