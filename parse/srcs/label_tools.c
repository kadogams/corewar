/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:25:03 by dazheng           #+#    #+#             */
/*   Updated: 2019/03/12 14:46:14 by dazheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		create_label(t_asm *env, char *line, int i)
{
	t_label	*new;

	if (!(new = (t_label*)malloc(sizeof(t_label))))
	{
		ft_dprintf(2, "Malloc failed\n");
		return (-1);
	}
	if ((new->name = ft_strsub(line, 0, i)) == NULL)
	{
		free(new);
		ft_dprintf(2, "Malloc failed\n");
		return (-1);
	}
	new->index = env->index;
	new->next = NULL;
	add_label(new, env);
	return (i + 1);
}

void	add_label_arg(t_label_arg *new, t_asm *env)
{
	t_label_arg	*begin;

	if (env->label_arg == NULL)
	{
		env->label_arg = new;
		return ;
	}
	begin = env->label_arg;
	new->next = begin;
	env->label_arg = new;
}

void	add_label(t_label *new, t_asm *env)
{
	t_label	*begin;

	if (env->label == NULL)
	{
		env->label = new;
		return ;
	}
	begin = env->label;
	new->next = begin;
	env->label = new;
}

int		is_label_char(char c)
{
	int	i;

	i = -1;
	while (LABEL_CHARS[++i])
	{
		if (c != LABEL_CHARS[i])
			continue ;
		break ;
	}
	if (c != '\0' && c == LABEL_CHARS[i])
		return (OK);
	return (KO);
}
