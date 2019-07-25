/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 09:03:47 by dazheng           #+#    #+#             */
/*   Updated: 2019/02/28 18:17:06 by dazheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		atoi_v2(char *str, int *nb, t_asm *env)
{
	int			i;
	long long	res;
	int			neg;

	i = 0;
	res = 0;
	neg = 1;
	if (str[i] == '-')
	{
		i++;
		env->cur_x += 1;
		neg = -1;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		res = res * 10 + str[i++] - '0';
		*nb = res * neg > 9223372036854775807 ? 1 : *nb;
		*nb = res * neg < -LONG_MAX - 1 ? -1 : *nb;
		env->cur_x += 1;
	}
	*nb = *nb == 0 ? res * neg : *nb;
	i += skip_whitespace(str + i, env, NO_UPDATE_X);
	return (str[i] == '\0' || str[i] == ',' ? OK : KO);
}

static int		get_reg(t_asm *env, t_arg *arg, char *line)
{
	if (arg->nb_arg == 3)
		return (KO);
	arg->type[arg->nb_arg] = REG_CODE;
	if (!atoi_v2(line, &arg->value[arg->nb_arg], env))
		return (KO);
	arg->nb_arg++;
	return (OK);
}

static int		get_dir(t_asm *env, t_arg *arg, char *line)
{
	if (arg->nb_arg == 3)
		return (KO);
	arg->type[arg->nb_arg] = DIR_CODE;
	arg->nb_arg++;
	if (line[0] == LABEL_CHAR)
		return (create_label_arg(env, arg, line + 1));
	if (!atoi_v2(line, &arg->value[arg->nb_arg - 1], env))
		return (KO);
	return (OK);
}

static int		get_ind(t_asm *env, t_arg *arg, char *line)
{
	if (arg->nb_arg == 3)
		return (KO);
	arg->type[arg->nb_arg] = IND_CODE;
	arg->nb_arg++;
	if (line[0] == LABEL_CHAR)
		return (create_label_arg(env, arg, line + 1));
	return (atoi_v2(line, &arg->value[arg->nb_arg - 1], env));
}

int				handle_arg(t_asm *env, t_arg *arg, int a, char *line)
{
	int	ret;
	int	i;

	i = 0;
	while (line[i])
	{
		if ((ret = skip_whitespace(line + i, env, UPDATE_X)) == -1)
			return (KO);
		i += ret;
		if (line[i] == DIRECT_CHAR)
			ret = get_dir(env, arg, line + i + 1);
		else if (line[i] == LABEL_CHAR || ft_isdigit(line[i]) || line[i] == '-')
			ret = get_ind(env, arg, line + i);
		else if (line[i] == 'r')
			ret = get_reg(env, arg, line + i + 1);
		else
			return (KO);
		if (ret == KO)
			return (KO);
		while (line[i] && line[i] != SEPARATOR_CHAR)
			i++;
		if (line[i] == SEPARATOR_CHAR)
			i++;
	}
	return (OK);
}
