/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 11:58:23 by dazheng           #+#    #+#             */
/*   Updated: 2019/03/15 10:38:13 by dazheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_pos(t_asm *env, t_arg *arg)
{
	int	pos;
	int	i;

	i = -1;
	pos = 1;
	pos += arg->oct_codage;
	while (++i < arg->nb_arg - 1)
	{
		if (arg->type[i] == REG_CODE)
			pos += 1;
		else if (arg->type[i] == IND_CODE)
			pos += 2;
		else
			pos += arg->dir_size;
	}
	return (pos);
}

static char	*get_label_name(t_asm *env, char *line)
{
	int	i;
	int	ret;

	i = -1;
	while (is_label_char(line[++i]))
		;
	if ((ret = skip_whitespace(line + i, env, NO_UPDATE_X)) == -1)
		return (NULL);
	if (line[ret + i] != '\0' && line[ret + i] != ',')
		return (NULL);
	else
		return (ft_strsub(line, 0, i));
}

static int	get_label_size(t_arg *arg)
{
	if (arg->type[arg->nb_arg - 1] == IND_CODE)
		return (2);
	else
		return (arg->dir_size);
}

int			create_label_arg(t_asm *env, t_arg *arg, char *line)
{
	t_label_arg	*new;

	if (!(new = (t_label_arg*)malloc(sizeof(t_label_arg))))
	{
		ft_dprintf(2, "Malloc failed\n");
		return (KO);
	}
	if ((new->label_name = get_label_name(env, line)) == NULL)
	{
		free(new);
		return (KO);
	}
	new->index_lab = env->index;
	new->pos = get_pos(env, arg) + env->index;
	new->label_size = get_label_size(arg);
	new->next = NULL;
	add_label_arg(new, env);
	return (OK);
}
