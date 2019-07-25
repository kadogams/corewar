/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 12:09:18 by dazheng           #+#    #+#             */
/*   Updated: 2019/03/05 11:36:24 by dazheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_error3(int option, t_asm *env)
{
	if (option == LFORK)
		ft_dprintf(2, "'lfork' malformated at line [%d]\nlfork: T_DIR\n",
		env->cur_y);
	else if (option == OR)
		ft_dprintf(2, "'or' malformated at line [%d]\nor: T_REG | T_DIR |"
		" T_IND, T_REG | T_DIR | T_IND, T_REG\n", env->cur_y);
	else if (option == CHAMP_MAX_SIZE)
		ft_dprintf(2, "Champion size is too big!\n");
	else if (option == AFF)
		ft_dprintf(2, "'aff' malformated at line [%d]\naff: T_REG\n",
				env->cur_y);
	else if (option == READ)
		ft_dprintf(2, "Can't read source file\n");
	else if (option == USAGE)
		ft_dprintf(2, "Usage: ./asm target_file.s\n");
	else if (option == REG)
		ft_dprintf(2, "Param REG must be between 1 and %d (included) "
		"at line [%d]\n", REG_NUMBER, env->cur_y);
	else if (option == NO_NAME)
		ft_dprintf(2, "Champion has no name\n");
	else
		return ;
}

static void	ft_error2(int option, t_asm *env)
{
	if (option == XOR)
		ft_dprintf(2, "'xor' malformated at line [%d]\nxor: T_REG| T_DIR | "
		"T_IND, T_REG | T_DIR | T_IND, T_REG\n", env->cur_y);
	else if (option == ZJMP)
		ft_dprintf(2, "'zjmp' malformated at line [%d]"
		"\nzjmp: T_DIR\n", env->cur_y);
	else if (option == LDI)
		ft_dprintf(2, "'ldi' malformated at line [%d]\nldi: T_REG| T_DIR | "
		"T_IND, T_REG | T_DIR, T_REG\n", env->cur_y);
	else if (option == STI)
		ft_dprintf(2, "'sti' malformated at line [%d]\nsti: T_REG, "
		"T_REG| T_DIR | T_IND, T_DIR | T_REG\n", env->cur_y);
	else if (option == FORK)
		ft_dprintf(2, "'fork' malformated at line [%d]\nfork: T_DIR\n",
				env->cur_y);
	else if (option == LLD)
		ft_dprintf(2, "'lld' malformated\nlld: T_DIR | T_IND, T_REG\n",
				env->cur_y);
	else if (option == LLDI)
		ft_dprintf(2, "'lldi' malformated at line [%d]\nlldi: T_REG| T_DIR | "
				"T_IND, T_REG| T_DIR, T_REG\n", env->cur_y);
	else if (option == NO_COMMENT)
		ft_dprintf(2, "Champion has no comment\n");
	else
		ft_error3(option, env);
}

int			ft_error(int option, t_asm *env)
{
	if (option == 1)
		ft_dprintf(2, "Lexical error TOKEN[%d:%d]\n", env->cur_y, env->cur_x);
	else if (option == LIVE)
		ft_dprintf(2, "'live' malformated at line [%d]\nlive: T_DIR\n",
				env->cur_y);
	else if (option == LD)
		ft_dprintf(2, "'ld' malformated at line [%d]\nld: T_DIR | T_IND, "
				"T_REG\n", env->cur_y);
	else if (option == ADD)
		ft_dprintf(2, "'add' malformated at line [%d]\nadd: T_REG, T_REG, "
				"T_REG\n", env->cur_y);
	else if (option == ST)
		ft_dprintf(2, "'st' malformated at line [%d]\nst: T_REG | T_IND, "
				"T_REG\n", env->cur_y);
	else if (option == SUB)
		ft_dprintf(2, "'sub' malformated at line [%d]\nsub: T_REG, T_REG, "
				"T_REG\n", env->cur_y);
	else if (option == AND)
		ft_dprintf(2, "'and' malformated at line [%d]\nand: T_REG | T_DIR | "
				"T_IND, T_REG | T_DIR | T_IND, T_REG\n", env->cur_y);
	else
		ft_error2(option, env);
	return (KO);
}
