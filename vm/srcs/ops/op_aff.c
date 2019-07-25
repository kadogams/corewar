/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 12:00:09 by skadogam          #+#    #+#             */
/*   Updated: 2019/03/09 09:08:03 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** AFF
** arg: {T_REG}
** affiche sur la sortie standard le char ASCII
*/

int		op_aff(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3])
{
	if (arg_type[0] == REG_CODE)
	{
		if (vm->opt_v & 4)
			verbosity_4(*pc, g_op[16], pc->arg, pc->arg_type);
		if (vm->opt_v & 16)
			verbosity_16(*pc, vm->arena, pc->index,
				pc->index + pc->arg_len + 1);
		if (vm->opt_aff & 1)
			ft_printf("AFF: %c\n", pc->reg[arg[0]] % 256);
	}
	pc->index += pc->arg_len + 1;
	return (OK);
}
