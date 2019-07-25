/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:35:09 by dazheng           #+#    #+#             */
/*   Updated: 2019/03/04 14:48:53 by dazheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	search_for_instr(t_asm *env, int i)
{
	int	start;
	int j;
	int	k;

	start = i;
	j = 0;
	k = 0;
	while (j < INSTR_SIZE)
	{
		while (env->line[i] == g_op[j].opcode[k])
		{
			if (g_op[j].size - 1 == k)
				return ((*g_op[j].ptr_fct)(env, j, env->line + start));
			i++;
			k++;
		}
		i = start;
		k = 0;
		j++;
	}
	return (ft_error(1, env));
}

static int	search_label(t_asm *env, char *line)
{
	int	i;

	i = 0;
	while (is_label_char(line[i]))
	{
		env->cur_x += 1;
		i++;
	}
	if (line[i] == LABEL_CHAR)
		return (create_label(env, line, i));
	return (KO);
}

int			parse_instructions(t_asm *env)
{
	int	i;
	int	ret;

	while ((ret = skip_blank_lines(env)) > 0)
	{
		if ((i = skip_whitespace(env->line, env, UPDATE_X)) == -1)
			return (KO);
		if ((ret = search_label(env, env->line + i)) == -1)
			return (KO);
		i += ret;
		if ((ret = skip_whitespace(env->line + i, env, UPDATE_X)) == -1)
			return (KO);
		i += ret;
		if (env->line[i] == '\0')
			continue ;
		if ((ret = search_for_instr(env, i)) == KO)
			return (KO);
		env->cur_x = 0;
		if (env->index >= CHAMP_MAX_SIZE)
			return (ft_error(CHAMP_MAX_SIZE, env));
	}
	if (ret == 0)
		return (OK);
	return (KO);
}
