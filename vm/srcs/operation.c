/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 16:34:27 by adefonta          #+#    #+#             */
/*   Updated: 2019/03/12 16:12:22 by adefonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_define_type(t_pc *pc, unsigned char byte)
{
	if (!byte || byte > 0x10)
		pc->index += 1;
	else
	{
		pc->op_code = byte;
		pc->count_down = g_op[byte].cycles - 2;
	}
}

int		op_treat(t_vm *vm, t_pc *pc)
{
	t_op	op;

	op = g_op[pc->op_code];
	if (args_manage(pc, op, vm->arena, pc->index))
	{
		if ((op.fct(vm, pc, pc->arg, pc->arg_type)) == KO)
		{
			vm->last_living_champi = NULL;
			return (KO);
		}
	}
	pc->op_code = 0;
	return (OK);
}
