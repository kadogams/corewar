/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:54:17 by skadogam          #+#    #+#             */
/*   Updated: 2019/03/06 17:42:00 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** LOAD INDEX
** arg: T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG
** additionne le resultat des deux premiers arguments,
** lis la valeur a l'adresse pointée par cette addition modulo IDX_MOD
** et la stocke dans le troisieme argument (sous la taille adéquate REG_SIZE)
*/

int		op_ldi(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3])
{
	int	a;
	int	b;

	if (arg_type[1] != IND_CODE && arg_type[2] == REG_CODE)
	{
		if (vm->opt_v & 4)
			verbosity_4(*pc, g_op[10], pc->arg, pc->arg_type);
		if (vm->opt_v & 16)
			verbosity_16(*pc, vm->arena, pc->index,
				pc->index + pc->arg_len + 1);
		a = arg_define(vm, pc, arg[0], arg_type[0]);
		b = arg_define(vm, pc, arg[1], arg_type[1]);
		pc->reg[arg[2]] = arg_read(vm->arena, pc->index + (a + b) % IDX_MOD,
			REG_SIZE);
	}
	pc->index += pc->arg_len + 1;
	return (OK);
}
