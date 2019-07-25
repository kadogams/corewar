/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:38:30 by adefonta          #+#    #+#             */
/*   Updated: 2019/03/12 16:15:58 by adefonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "macro.h"
# include "visu_macro.h"

typedef struct	s_champi
{
	int				index;
	int				number;
	int				weight;
	int				nb_live;
	int				last_live;
	int				color;
	int				nb_process;
	char			*name;
	char			*cmt;
}				t_champi;

typedef struct	s_pc
{
	int				nb;
	unsigned int	index;
	unsigned int	pre_index;
	int				carry;
	int				reg[NB_REGISTRE];
	int				op_code;
	int				live;
	int				arg_len;
	int				arg[3];
	char			arg_type[3];
	int				count_down;
	t_champi		*champi;
	struct s_pc		*next;
}				t_pc;

typedef struct	s_vm
{
	char			opt_aff;
	char			opt_g;
	char			opt_v;
	int				opt_dump;
	int				nb_process;
	int				tot_process;
	int				nb_champi;
	int				cycles;
	int				tot_cycles;
	int				checkups;
	int				cycles_to_die;
	int				live_calls;
	int				next_max_checks_cycles;
	unsigned char	arena[MEM_SIZE];
	int				arena_champi[MEM_SIZE];
	t_champi		*champi[MAX_PLAYERS];
	t_champi		*last_living_champi;
	t_pc			*pc;
}				t_vm;

typedef struct	s_op
{
	int				nb_arg;
	int				dir_len;
	int				arg_type_one;
	int				cycles;
	char			coding_byte;
	char			*opcode;
	int				(*fct)(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3]);
}				t_op;

#endif
