/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fct3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 17:22:53 by dazheng           #+#    #+#             */
/*   Updated: 2019/03/04 12:43:55 by dazheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_sti(t_asm *env, int i, char *line)
{
	int		k;
	t_arg	arg;

	init_arg(&arg, 2, 1);
	line = line + g_op[i].size;
	env->cur_x += g_op[i].size;
	if (!handle_arg(env, &arg, 0, line) || arg.nb_arg != 3 || arg.type[0] !=
	REG_CODE || (arg.type[2] != DIR_CODE && arg.type[2] != REG_CODE))
		return (ft_error(STI, env));
	k = -1;
	env->code[env->index++] = 0x0B;
	env->code[env->index++] = get_codage(arg);
	while (++k < arg.nb_arg)
	{
		if (!fill_code(env, arg.type[k], arg.value[k], 2))
			return (KO);
	}
	return (OK);
}

int		ft_fork(t_asm *env, int i, char *line)
{
	int		k;
	t_arg	arg;

	init_arg(&arg, 2, 0);
	line = line + g_op[i].size;
	env->cur_x += g_op[i].size;
	if (!handle_arg(env, &arg, 0, line) || arg.nb_arg != 1 || arg.type[0] !=
	DIR_CODE)
		return (ft_error(FORK, env));
	k = -1;
	env->code[env->index++] = 0x0C;
	while (++k < arg.nb_arg)
	{
		if (!fill_code(env, arg.type[k], arg.value[k], 2))
			return (KO);
	}
	return (OK);
}

int		ft_lld(t_asm *env, int i, char *line)
{
	int		k;
	t_arg	arg;

	init_arg(&arg, 4, 1);
	line = line + g_op[i].size;
	env->cur_x += g_op[i].size;
	if (!handle_arg(env, &arg, 0, line) || arg.nb_arg != 2 || (arg.type[0] !=
	DIR_CODE && arg.type[0] != IND_CODE) || arg.type[1] != REG_CODE)
		return (ft_error(LLD, env));
	k = -1;
	env->code[env->index++] = 0x0D;
	env->code[env->index++] = get_codage(arg);
	while (++k < arg.nb_arg)
	{
		if (!fill_code(env, arg.type[k], arg.value[k], 4))
			return (KO);
	}
	return (OK);
}

int		ft_lldi(t_asm *env, int i, char *line)
{
	int		k;
	t_arg	arg;

	init_arg(&arg, 2, 1);
	line = line + g_op[i].size;
	env->cur_x += g_op[i].size;
	if (!handle_arg(env, &arg, 0, line) || arg.nb_arg != 3 || (arg.type[1] !=
	REG_CODE && arg.type[1] != DIR_CODE) || arg.type[2] != REG_CODE)
		return (ft_error(LLDI, env));
	k = -1;
	env->code[env->index++] = 0x0E;
	env->code[env->index++] = get_codage(arg);
	while (++k < arg.nb_arg)
	{
		if (!fill_code(env, arg.type[k], arg.value[k], 2))
			return (KO);
	}
	return (OK);
}

int		ft_lfork(t_asm *env, int i, char *line)
{
	int		k;
	t_arg	arg;

	init_arg(&arg, 2, 0);
	line = line + g_op[i].size;
	env->cur_x += g_op[i].size;
	if (!handle_arg(env, &arg, 0, line) || arg.nb_arg != 1 || arg.type[0] !=
	DIR_CODE)
		return (ft_error(LFORK, env));
	k = -1;
	env->code[env->index++] = 0x0F;
	while (++k < arg.nb_arg)
	{
		if (!fill_code(env, arg.type[k], arg.value[k], 2))
			return (KO);
	}
	return (OK);
}
