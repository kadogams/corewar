/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:50:48 by dazheng           #+#    #+#             */
/*   Updated: 2019/03/12 14:55:01 by dazheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	fill_prog_name(t_header *header, t_asm *env, char *line)
{
	static int	index = 0;
	int			i;

	i = 0;
	while (line[i] && line[i] != '"' && index < PROG_NAME_LENGTH)
		header->prog_name[index++] = line[i++];
	env->cur_x += i + 1;
	if (index == PROG_NAME_LENGTH && line[i] != '"')
		return (-1);
	else if (line[i] == '"')
		return (1);
	else
		header->prog_name[index++] = '\n';
	return (0);
}

static int	fill_comment(t_header *header, t_asm *env, char *line)
{
	static int	index = 0;
	int			i;

	i = 0;
	while (line[i] && line[i] != '"' && index < COMMENT_LENGTH)
		header->comment[index++] = line[i++];
	env->cur_x += i;
	if (index > COMMENT_LENGTH && line[i] != '"')
		return (-1);
	else if (line[i] == '"')
		return (1);
	else
		header->comment[index++] = '\n';
	return (0);
}

static int	parse_comment(t_header *header, t_asm *env)
{
	int		ret;
	int		i;

	ft_bzero(header->comment, COMMENT_LENGTH);
	if (skip_blank_lines(env) != 1 || (i = skip_whitespace(env->line, env,
	UPDATE_X)) == -1 || ft_strncmp(env->line + i, ".comment", 8))
		return (ft_error(NO_COMMENT, env));
	env->cur_x += 8;
	if ((ret = skip_whitespace(env->line + i + 8, env, UPDATE_X)) == -1)
		return (KO);
	i = ret + i + 8;
	if (env->line[i] != '"')
		return (ft_error(1, env));
	env->cur_x += 1;
	if ((ret = fill_comment(header, env, env->line + i + 1)) == 1)
		return (check_last_line(env->line, 1, env));
	while (ret != -1 && get_next_line_v2(env->fd_s, &env->line, 0) > 0)
	{
		env->cur_x = 0;
		env->cur_y += 1;
		if ((ret = fill_comment(header, env, env->line)) == 1)
			return (check_last_line(env->line, 0, env));
		ft_strdel(&env->line);
	}
	return (ft_error(1, env));
}

static int	parse_name(t_header *header, t_asm *env)
{
	int		ret;
	int		i;

	ft_bzero(header->prog_name, PROG_NAME_LENGTH);
	if (skip_blank_lines(env) != 1 || (i = skip_whitespace(env->line, env,
	UPDATE_X)) == -1 || ft_strncmp(env->line + i, ".name", 5))
		return (ft_error(NO_NAME, env));
	env->cur_x += 5;
	if ((ret = skip_whitespace(env->line + i + 5, env, UPDATE_X)) == -1)
		return (KO);
	i = ret + i + 5;
	if (env->line[i] != '"')
		return (ft_error(1, env));
	env->cur_x += 1;
	if ((ret = fill_prog_name(header, env, env->line + i + 1)) == 1)
		return (check_last_line(env->line, 1, env));
	while (ret != -1 && get_next_line_v2(env->fd_s, &env->line, 0) > 0)
	{
		env->cur_x = 0;
		env->cur_y += 1;
		if ((ret = fill_prog_name(header, env, env->line)) == 1)
			return (check_last_line(env->line, 0, env));
		ft_strdel(&env->line);
	}
	return (ft_error(1, env));
}

int			start_parsing(t_header *header, t_asm *env)
{
	if (!parse_name(header, env))
		return (KO);
	if (!parse_comment(header, env))
		return (KO);
	if (!parse_instructions(env))
		return (KO);
	if (env->code[0] == '\0')
	{
		ft_printf("No instructions in file\n");
		return (KO);
	}
	if (!manage_labels(env))
		return (KO);
	return (OK);
}
