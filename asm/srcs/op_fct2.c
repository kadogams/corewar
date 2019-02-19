/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fct2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 17:01:42 by dazheng           #+#    #+#             */
/*   Updated: 2019/02/18 18:14:05 by dazheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_and(t_asm *env, int i, char *line)
{
	int	k;
	t_arg arg;

	ft_printf("AND\n");
	init_arg(&arg, 4, 1);
	line = line + g_op[i].size;
	ft_printf("LIIIINE DE AND = |%s|\n", line);
	env->cur_x += g_op[i].size;
	if (!handle_arg(env, &arg, 0, line) || arg.nb_arg != 3 || arg.type[2] !=
	REG_CODE)
		return (KO);
	k = -1;
	env->code[env->index++] = 0x06;
	env->code[env->index++] = get_codage(arg);
	while (++k < arg.nb_arg)
		fill_code(env, arg.type[k], arg.value[k], 4);
	return (OK);
}

int		ft_or(t_asm *env, int i, char *line)
{
	int	k;
	t_arg arg;

	ft_printf("OR\n");
	init_arg(&arg, 4, 1);
	line = line + g_op[i].size;
	env->cur_x += g_op[i].size;
	if (!handle_arg(env, &arg, 0, line) || arg.nb_arg != 3 || arg.type[2] !=
	REG_CODE)
		return (KO);
	k = -1;
	env->code[env->index++] = 0x07;
	env->code[env->index++] = get_codage(arg);
	while (++k < arg.nb_arg)
		fill_code(env, arg.type[k], arg.value[k], 4);
	return (OK);

}

int		ft_xor(t_asm *env, int i, char *line)
{
	int	k;
	t_arg arg;

	ft_printf("XOR\n");
	init_arg(&arg, 4, 1);
	line = line + g_op[i].size;
	env->cur_x += g_op[i].size;
	if (!handle_arg(env, &arg, 0, line) || arg.nb_arg != 3 || arg.type[2] !=
	REG_CODE)
		return (KO);
	k = -1;
	env->code[env->index++] = 0x08;
	env->code[env->index++] = get_codage(arg);
	while (++k < arg.nb_arg)
		fill_code(env, arg.type[k], arg.value[k], 4);
	return (OK);
}

int		ft_zjmp(t_asm *env, int i, char *line)
{
	int	k;
	t_arg arg;

	ft_printf("ZJMP\n");
	init_arg(&arg, 2, 0);
	line = line + g_op[i].size;
	env->cur_x += g_op[i].size;
	if (!handle_arg(env, &arg, 0, line) || arg.nb_arg != 1 ||
	arg.type[0] != DIR_CODE)
		return (KO);
	k = -1;
	env->code[env->index++] = 0x09;
	while (++k < arg.nb_arg)
		fill_code(env, arg.type[k], arg.value[k], 2);
	return (OK);
}

int		ft_ldi(t_asm *env, int i, char *line)
{
	int	k;
	t_arg arg;

	ft_printf("LDI\n");
	init_arg(&arg, 2, 1);
	line = line + g_op[i].size;
	env->cur_x += g_op[i].size;
	if (!handle_arg(env, &arg, 0, line) || arg.nb_arg != 3 || (arg.type[1] != 
	REG_CODE && arg.type[1] != DIR_CODE) || arg.type[2] != REG_CODE)
		return (KO);
	k = -1;
	env->code[env->index++] = 0x0A;
	env->code[env->index++] = get_codage(arg);
	while (++k < arg.nb_arg)
		fill_code(env, arg.type[k], arg.value[k], 2);
	return (OK);
}