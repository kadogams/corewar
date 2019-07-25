/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:49:06 by skadogam          #+#    #+#             */
/*   Updated: 2019/03/06 17:41:43 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** AND
** arg: {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}
** applique un & binaire sur les 2 premiers params, et met le résultat dans
** le 3eme
*/

int		op_and(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3])
{
	int	a;
	int	b;

	pc->carry = 0;
	if (arg_type[2] == REG_CODE)
	{
		if (vm->opt_v & 4)
			verbosity_4(*pc, g_op[6], pc->arg, pc->arg_type);
		if (vm->opt_v & 16)
			verbosity_16(*pc, vm->arena, pc->index,
				pc->index + pc->arg_len + 1);
		a = arg_define(vm, pc, arg[0], arg_type[0]);
		b = arg_define(vm, pc, arg[1], arg_type[1]);
		if (!(pc->reg[arg[2]] = a & b))
			pc->carry = 1;
	}
	pc->index += pc->arg_len + 1;
	return (OK);
}
