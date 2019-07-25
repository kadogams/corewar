/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:55:00 by skadogam          #+#    #+#             */
/*   Updated: 2019/03/06 17:43:00 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** STORE INDEX
** arg: {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}
** additionne les 2 derniers params, utilise cette somme comme une adresse ou
** sera copiee la valeur du 1er param
*/

int		op_sti(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3])
{
	int				a;
	int				b;
	unsigned int	index;

	if (arg_type[0] == REG_CODE && arg_type[2] != IND_CODE)
	{
		if (vm->opt_v & 4)
			verbosity_4(*pc, g_op[11], pc->arg, pc->arg_type);
		if (vm->opt_v & 16)
			verbosity_16(*pc, vm->arena, pc->index,
				pc->index + pc->arg_len + 1);
		a = arg_define(vm, pc, arg[1], arg_type[1]);
		b = arg_define(vm, pc, arg[2], arg_type[2]);
		index = pc->index + (a + b) % IDX_MOD;
		index %= MEM_SIZE;
		tools_memcpy_int(vm, index, pc->reg[arg[0]]);
		arena_colors(vm, *pc, index, 4);
	}
	pc->index += pc->arg_len + 1;
	return (OK);
}
