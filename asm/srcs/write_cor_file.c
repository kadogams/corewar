/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cor_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:28:41 by dazheng           #+#    #+#             */
/*   Updated: 2019/02/22 17:31:12 by dazheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_magic_size(t_asm *env)
{
	int	bits;
	int	i;

	i = 0;
	bits = 24;
	while (bits >= 0)
	{
		env->magic[i++] = (COREWAR_EXEC_MAGIC >> bits) & 0b11111111;
		bits -= 8;
	}
	bits = 56;
	i = 0;
	while (bits >= 0)
	{
		if (bits <= 24)
			env->size[i++] = (env->index >> bits) & 0b11111111;
		else
			env->size[i++] = 0;
		bits -= 8;
	}
}

void		write_cor_file(t_asm *env, header_t *header)
{
	int	i;

	i = 0;
	write_magic_size(env);
	write(env->fd_cor, env->magic, 4);
	write(env->fd_cor, header->prog_name, PROG_NAME_LENGTH);
	write(env->fd_cor, env->size, 8);
	write(env->fd_cor, header->comment, COMMENT_LENGTH);
	while (i < 4)
	{
		ft_putchar_fd(0, env->fd_cor);
		i++;
	}
	write(env->fd_cor, env->code, env->index);
}
