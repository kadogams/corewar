/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:43:52 by skadogam          #+#    #+#             */
/*   Updated: 2019/03/06 17:42:57 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** STORE
** arg: {T_REG, T_IND | T_REG}
** stocke la valeur du registre vers le second paramètre
*/

int		op_st(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3])
{
	unsigned int	index;

	if (arg_type[0] == REG_CODE && arg_type[1] != DIR_CODE)
	{
		if (vm->opt_v & 4)
			verbosity_4(*pc, g_op[3], pc->arg, pc->arg_type);
		if (vm->opt_v & 16)
			verbosity_16(*pc, vm->arena, pc->index,
				pc->index + pc->arg_len + 1);
		if (pc->arg_type[1] == REG_CODE)
			pc->reg[arg[1]] = pc->reg[arg[0]];
		else
		{
			index = pc->index + arg[1] % IDX_MOD;
			index %= MEM_SIZE;
			tools_memcpy_int(vm, index, pc->reg[arg[0]]);
			arena_colors(vm, *pc, index, 4);
		}
	}
	pc->index += pc->arg_len + 1;
	return (OK);
}
