/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 13:21:39 by dazheng           #+#    #+#             */
/*   Updated: 2019/03/12 14:54:26 by dazheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_valid(char *file)
{
	int len;

	len = ft_strlen(file);
	if (len > 2 && !ft_strcmp(".s", file + len - 2))
		return (OK);
	return (KO);
}

static char	*parse_file_name(char *file)
{
	char	*name;
	char	*tmp;
	int		len;

	len = ft_strlen(file);
	if ((name = ft_strsub(file, 0, len - 2)) == NULL)
		return (NULL);
	if ((name = ft_strjoin_free_s1(name, ".cor")) == NULL)
		return (NULL);
	return (name);
}

static int	open_cor_file(char *file, t_asm *env)
{
	env->output = parse_file_name(file);
	if (env->output == NULL)
	{
		ft_dprintf(2, "Malloc failed\n");
		return (KO);
	}
	if ((env->fd_cor = open(env->output, O_CREAT | O_RDWR | O_TRUNC, 0644))
			== -1)
	{
		ft_dprintf(2, "Failed to create %s\n", env->output);
		return (KO);
	}
	return (OK);
}

int			main(int ac, char **av)
{
	t_header	header;
	t_asm		env;

	if (ac == 2 && check_valid(av[1]))
	{
		init_env(&env);
		if ((env.fd_s = open(av[1], O_RDONLY)) == -1)
			return (ft_error(READ, &env));
		if (!start_parsing(&header, &env))
			return (free_all(&env));
		else
		{
			if (!open_cor_file(av[1], &env))
				return (free_all(&env));
			write_cor_file(&env, &header);
			ft_printf("Writing output program to %s\n", env.output);
		}
	}
	else
		return (ft_error(USAGE, &env));
	free_all(&env);
	return (0);
}
