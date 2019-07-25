/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fct4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 17:32:04 by dazheng           #+#    #+#             */
/*   Updated: 2019/03/04 12:47:10 by dazheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_aff(t_asm *env, int i, char *line)
{
	int		k;
	t_arg	arg;

	init_arg(&arg, 0, 1);
	line = line + g_op[i].size;
	env->cur_x += g_op[i].size;
	if (!handle_arg(env, &arg, 0, line) || arg.nb_arg != 1 || arg.type[0] !=
	REG_CODE)
		return (ft_error(AFF, env));
	k = -1;
	env->code[env->index++] = 0x10;
	env->code[env->index++] = get_codage(arg);
	while (++k < arg.nb_arg)
	{
		if (!fill_code(env, arg.type[k], arg.value[k], 0))
			return (KO);
	}
	return (OK);
}

int		get_codage(t_arg arg)
{
	int	res;

	res = (arg.type[0] & 0b11111111) << 6;
	res += (arg.type[1] & 0b11111111) << 4;
	res += (arg.type[2] & 0b11111111) << 2;
	return (res);
}

int		fill_code(t_asm *env, int type, int value, int octet)
{
	int	bits;

	if (type == 1)
	{
		if (value < 1 || value > REG_NUMBER)
			return (ft_error(REG, env));
		env->code[env->index++] = value;
	}
	else if (type == 3)
	{
		env->code[env->index++] = (value >> 8) & 0b11111111;
		env->code[env->index++] = value & 0b11111111;
	}
	else if (type == 2)
	{
		bits = octet == 2 ? 8 : 24;
		while (bits >= 0)
		{
			env->code[env->index++] = (value >> bits) & 0b11111111;
			bits -= 8;
		}
	}
	else
		return (KO);
	return (OK);
}
