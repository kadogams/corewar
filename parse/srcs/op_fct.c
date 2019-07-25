/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:03:57 by dazheng           #+#    #+#             */
/*   Updated: 2019/03/04 14:10:23 by dazheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_live(t_asm *env, int i, char *line)
{
	int		k;
	t_arg	arg;

	init_arg(&arg, 4, 0);
	line = line + g_op[i].size;
	env->cur_x += g_op[i].size;
	if (!handle_arg(env, &arg, 0, line) || arg.type[0] != DIR_CODE
			|| arg.nb_arg != 1)
		return (ft_error(LIVE, env));
	env->code[env->index++] = 0x01;
	fill_code(env, arg.type[0], arg.value[0], 4);
	return (OK);
}

int		ft_ld(t_asm *env, int i, char *line)
{
	int		k;
	t_arg	arg;

	init_arg(&arg, 4, 1);
	line = line + g_op[i].size;
	env->cur_x += g_op[i].size;
	if (!handle_arg(env, &arg, 0, line) || arg.nb_arg != 2 ||
	(arg.type[0] != IND_CODE && arg.type[0] != DIR_CODE) ||
	arg.type[1] != REG_CODE)
		return (ft_error(LD, env));
	k = -1;
	env->code[env->index++] = 0x02;
	env->code[env->index++] = get_codage(arg);
	while (++k < arg.nb_arg)
	{
		if (!fill_code(env, arg.type[k], arg.value[k], 4))
			return (KO);
	}
	return (OK);
}

int		ft_st(t_asm *env, int i, char *line)
{
	int		k;
	t_arg	arg;

	init_arg(&arg, 0, 1);
	line = line + g_op[i].size;
	env->cur_x += g_op[i].size;
	if (!handle_arg(env, &arg, 0, line) || arg.nb_arg != 2 ||
	(arg.type[1] != REG_CODE && arg.type[1] != IND_CODE) || arg.type[0] !=
	REG_CODE)
		return (ft_error(ST, env));
	k = -1;
	env->code[env->index++] = 0x03;
	env->code[env->index++] = get_codage(arg);
	while (++k < arg.nb_arg)
	{
		if (!fill_code(env, arg.type[k], arg.value[k], 0))
			return (KO);
	}
	return (OK);
}

int		ft_add(t_asm *env, int i, char *line)
{
	int		k;
	t_arg	arg;

	init_arg(&arg, 0, 1);
	line = line + g_op[i].size;
	env->cur_x += g_op[i].size;
	if (!handle_arg(env, &arg, 0, line) || arg.nb_arg != 3 ||
	arg.type[0] != REG_CODE || arg.type[1] != REG_CODE || arg.type[2] !=
	REG_CODE)
		return (ft_error(ADD, env));
	k = -1;
	env->code[env->index++] = 0x04;
	env->code[env->index++] = get_codage(arg);
	while (++k < arg.nb_arg)
	{
		if (!fill_code(env, arg.type[k], arg.value[k], 0))
			return (KO);
	}
	return (OK);
}

int		ft_sub(t_asm *env, int i, char *line)
{
	int		k;
	t_arg	arg;

	init_arg(&arg, 0, 1);
	line = line + g_op[i].size;
	env->cur_x += g_op[i].size;
	if (!handle_arg(env, &arg, 0, line) || arg.nb_arg != 3 ||
	arg.type[0] != REG_CODE || arg.type[1] != REG_CODE || arg.type[2] !=
	REG_CODE)
		return (ft_error(SUB, env));
	k = -1;
	env->code[env->index++] = 0x05;
	env->code[env->index++] = get_codage(arg);
	while (++k < arg.nb_arg)
	{
		if (!fill_code(env, arg.type[k], arg.value[k], 0))
			return (KO);
	}
	return (OK);
}
