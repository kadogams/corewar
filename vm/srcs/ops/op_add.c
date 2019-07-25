/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:45:27 by skadogam          #+#    #+#             */
/*   Updated: 2019/03/06 17:36:03 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ADD
** arg: {T_REG, T_REG, T_REG}
** additionne les 2 premiers registres, et met le résultat dans le 3eme
*/

int		op_add(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3])
{
	pc->carry = 0;
	if (arg_type[0] == REG_CODE && arg_type[1] == REG_CODE
		&& arg_type[2] == REG_CODE)
	{
		if (vm->opt_v & 4)
			verbosity_4(*pc, g_op[4], pc->arg, pc->arg_type);
		if (vm->opt_v & 16)
			verbosity_16(*pc, vm->arena, pc->index,
				pc->index + pc->arg_len + 1);
		if (!(pc->reg[arg[2]] = pc->reg[arg[0]] + pc->reg[arg[1]]))
			pc->carry = 1;
	}
	pc->index += pc->arg_len + 1;
	return (OK);
}
