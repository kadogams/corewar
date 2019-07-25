/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:58:56 by dazheng           #+#    #+#             */
/*   Updated: 2019/03/04 14:29:17 by dazheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		ft_error_label(char *label)
{
	ft_printf("Label '%s' not found\n", label);
	return (KO);
}

static t_label	*find_label(t_asm *env, char *name)
{
	t_label	*label;

	label = env->label;
	while (label)
	{
		if (!ft_strcmp(label->name, name))
			break ;
		label = label->next;
	}
	return (label);
}

static void		fill_label(t_asm *env, t_label *label, t_label_arg *arg)
{
	int	value;
	int	bits;

	value = label->index - arg->index_lab;
	bits = arg->label_size == 2 ? 8 : 24;
	while (bits >= 0)
	{
		env->code[arg->pos++] = (value >> bits) & 0b11111111;
		bits -= 8;
	}
}

int				manage_labels(t_asm *env)
{
	t_label_arg	*tmp;
	t_label		*label;

	tmp = env->label_arg;
	while (tmp)
	{
		if (!(label = find_label(env, tmp->label_name)))
			return (ft_error_label(tmp->label_name));
		fill_label(env, label, tmp);
		tmp = tmp->next;
	}
	return (OK);
}
