/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:59:54 by dazheng           #+#    #+#             */
/*   Updated: 2019/03/12 14:45:27 by dazheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	free_label(t_label *label)
{
	t_label	*tmp;

	while (label)
	{
		free(label->name);
		tmp = label->next;
		free(label);
		label = tmp;
	}
	free(label);
}

static void	free_label_arg(t_label_arg *label)
{
	t_label_arg	*tmp;

	while (label)
	{
		free(label->label_name);
		tmp = label->next;
		free(label);
		label = tmp;
	}
	free(label);
}

int			free_all(t_asm *env)
{
	free_label(env->label);
	free_label_arg(env->label_arg);
	free(env->output);
	free(env->line);
	while (get_next_line_v2(env->fd_s, &env->line, 0) > 0)
		ft_strdel(&env->line);
	close(env->fd_s);
	close(env->fd_cor);
	return (0);
}
