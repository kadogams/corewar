/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 11:11:27 by skadogam          #+#    #+#             */
/*   Updated: 2019/07/13 12:03:14 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <fcntl.h>
# include "libftprintf.h"
# include "struct.h"
# include "macro.h"

void		and_the_winner_is(t_vm *vm, t_champi *champi);

int			arena_visu(t_vm *vm);
int			arena_manage(t_vm *vm);
int			arena_next_cycle(t_vm *vm);
void		arena_colors(t_vm *vm, t_pc pc, unsigned int index, int jump);

int			arg_read(unsigned char *arena, unsigned int index, int len);
int			args_manage(t_pc *pc, t_op op, unsigned char *arena, int index);
int			arg_define(t_vm *vm, t_pc *pc, int arg, int type);

int			champi_reset_live(t_vm *vm);
t_champi	*champi_init(t_vm *vm, int index, long number);

int			dump(t_vm *vm);

void		*error_null(char *error);
int			error_int(char *error);
int			error_source_file(char *name);
int			error_header(char *name);
int			error_size(char *name);

long		flags_get(t_vm *vm, int ac, char **av, int *i);

void		free_champi_list(t_champi *champi[MAX_PLAYERS], int nb_player);
void		free_pc_list(t_pc *pc);

void		init_vm(t_vm *vm);
int			init_pc(t_vm *vm, t_champi *champi, unsigned int index);

void		introduction(t_champi **champi);

int			op_treat(t_vm *vm, t_pc *pc);
void		op_define_type(t_pc *pc, unsigned char byte);

int			op_live(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3]);
int			op_ld(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3]);
int			op_st(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3]);
int			op_add(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3]);
int			op_sub(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3]);
int			op_and(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3]);
int			op_or(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3]);
int			op_xor(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3]);
int			op_zjmp(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3]);
int			op_ldi(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3]);
int			op_sti(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3]);
int			op_fork(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3]);
int			op_lld(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3]);
int			op_lldi(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3]);
int			op_lfork(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3]);
int			op_aff(t_vm *vm, t_pc *pc, int arg[3], char arg_type[3]);

int			parse_champi(t_vm *vm, int ac, char **av, t_list **champi_lst);

int			pc_init_all(t_vm *vm, t_list **champi_lst);
void		pc_copy(t_pc *dest, t_pc *src);
int			pc_alive(t_vm *vm);

void		put_neutral(int n);
void		put_red(int n);
void		put_blue(int n);
void		put_green(int n);
void		put_yellow(int n);
void		put_cyan(int n);
void		put_mauve(int n);

void		sort_champi_by_number(t_vm *vm, t_list **champi_lst);

void		tools_memcpy_int(t_vm *vm, unsigned int index, int n);

void		verbosity_4(t_pc pc, t_op op, int arg[3], char arg_type[3]);
void		verbosity_16(t_pc pc, unsigned char *arena, int index, int len);

int			vm_usage(void);

static const t_op	g_op[17] = {
	{0, 0, 0, 0, 0, "null", NULL},
	{1, 4, T_DIR, 10, 0, "live", op_live},
	{2, 4, 0, 5, 1, "ld", op_ld},
	{2, 4, 0, 5, 1, "st", op_st},
	{3, 4, 0, 10, 1, "add", op_add},
	{3, 4, 0, 10, 1, "sub", op_sub},
	{3, 4, 0, 6, 1, "and", op_and},
	{3, 4, 0, 6, 1, "or", op_or},
	{3, 4, 0, 6, 1, "xor", op_xor},
	{1, 2, T_DIR, 20, 0, "zjmp", op_zjmp},
	{3, 2, 0, 25, 1, "ldi", op_ldi},
	{3, 2, 0, 25, 1, "sti", op_sti},
	{1, 2, T_DIR, 800, 0, "fork", op_fork},
	{2, 4, 0, 10, 1, "lld", op_lld},
	{3, 2, 0, 50, 1, "lldi", op_lldi},
	{1, 2, T_DIR, 1000, 0, "lfork", op_lfork},
	{1, 4, T_REG, 2, 1, "aff", op_aff},
};

#endif
