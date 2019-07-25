/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:51:27 by skadogam          #+#    #+#             */
/*   Updated: 2019/03/06 17:43:07 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** XOR
** arg: {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}
** fait un ^
*/

int		op_xor(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3])
{
	int	a;
	int	b;

	pc->carry = 0;
	if (arg_type[2] == REG_CODE)
	{
		if (vm->opt_v & 4)
			verbosity_4(*pc, g_op[8], pc->arg, pc->arg_type);
		if (vm->opt_v & 16)
			verbosity_16(*pc, vm->arena, pc->index,
				pc->index + pc->arg_len + 1);
		a = arg_define(vm, pc, arg[0], arg_type[0]);
		b = arg_define(vm, pc, arg[1], arg_type[1]);
		if (!(pc->reg[arg[2]] = a ^ b))
			pc->carry = 1;
	}
	pc->index += pc->arg_len + 1;
	return (OK);
}
