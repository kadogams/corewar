/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 23:43:31 by adefonta          #+#    #+#             */
/*   Updated: 2019/03/06 16:22:57 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "macro.h"

static int	check_type(unsigned char coding_byte, int id)
{
	char	type;

	if (id == 0)
		coding_byte >>= 6;
	else if (id == 1)
		coding_byte >>= 4;
	else if (id == 2)
		coding_byte >>= 2;
	type = coding_byte & 0b11;
	return ((int)type);
}

static int	len_arg(t_op op, int arg_type)
{
	if (!arg_type)
		return (0);
	else if (arg_type == REG_CODE)
		return (1);
	else if (arg_type == IND_CODE)
		return (2);
	return (op.dir_len);
}

int			arg_read(unsigned char *arena, unsigned int index, int len)
{
	int				i;
	int				value;

	i = 0;
	value = 0x0;
	while (i < len)
	{
		value <<= 8;
		value |= arena[(index + i++) % MEM_SIZE];
	}
	if (len == 2)
		return ((int)(short)value);
	return (value);
}

int			arg_define(t_vm *vm, t_pc *pc, int arg, int type)
{
	int	value;

	if (type != IND_CODE)
		value = (type == REG_CODE) ? pc->reg[arg] : arg;
	else
		value = arg_read(vm->arena, pc->index + arg, REG_SIZE);
	return (value);
}

int			args_manage(t_pc *pc, t_op op, unsigned char *arena, int index)
{
	int				i;
	int				len;
	int				len_tot;
	int				ret;

	i = -1;
	len = 0;
	len_tot = 0;
	ret = OK;
	while (++i < op.nb_arg)
	{
		pc->arg_type[i] = !op.coding_byte ? op.arg_type_one :
			check_type(arena[index + 1], i);
		len = len_arg(op, pc->arg_type[i]);
		pc->arg[i] = arg_read(arena, index + len_tot + op.coding_byte + 1, len);
		len_tot += len;
		if (pc->arg_type[i] == REG_CODE &&
			(pc->arg[i] < 1 || pc->arg[i] > REG_NUMBER))
			ret = KO;
	}
	pc->arg_len = len_tot + op.coding_byte;
	return (ret);
}
