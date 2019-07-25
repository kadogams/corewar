/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:35:46 by dazheng           #+#    #+#             */
/*   Updated: 2019/03/05 11:36:29 by dazheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "op.h"
# include "libftprintf.h"
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>

# define UPDATE_X 1
# define NO_UPDATE_X 0
# define INSTR_SIZE 16
# define LIVE 2
# define INSTR 3
# define LD 4
# define ADD 5
# define ST 6
# define SUB 7
# define AND 8
# define OR 9
# define XOR 10
# define ZJMP 11
# define LDI 12
# define STI 13
# define FORK 14
# define LLD 15
# define LLDI 16
# define LFORK 17
# define AFF 18
# define READ 19
# define USAGE 20
# define REG 21
# define NO_NAME 22
# define NO_COMMENT 23

typedef struct		s_asm
{
	int					cur_x;
	int					cur_y;
	int					fd_s;
	int					fd_cor;
	char				*output;
	char				*line;
	unsigned char		magic[4];
	unsigned char		size[8];
	unsigned char		code[CHAMP_MAX_SIZE + 24];
	int					index;
	struct s_label		*label;
	struct s_label_arg	*label_arg;
}					t_asm;

typedef struct		s_arg
{
	int				nb_arg;
	int				value[3];
	int				type[3];
	int				oct_codage;
	int				dir_size;
}					t_arg;

typedef struct		s_label
{
	char			*name;
	int				index;
	struct s_label	*next;
}					t_label;

typedef struct		s_label_arg
{
	char				*label_name;
	int					index_lab;
	int					pos;
	int					label_size;
	struct s_label_arg	*next;
}					t_label_arg;

typedef struct		s_op
{
	char			*opcode;
	int				size;
	int				(*ptr_fct)(t_asm *env, int i, char *line);
}					t_op;

/*
** error.c
*/

int					ft_error(int option, t_asm *env);

/*
** handle_arg.c
*/

int					handle_arg(t_asm *env, t_arg *arg, int i, char *line);

/*
** init.c
*/

int					init_env(t_asm *env);
void				init_arg(t_arg *arg, int dir_size, int oct_codage);

/*
** label.c
*/

int					create_label_arg(t_asm *env, t_arg *arg, char *line);

/*
** label_management.c
*/

int					manage_labels(t_asm *env);

/*
** label_tools.c
*/

int					create_label(t_asm *env, char *line, int i);
void				add_label_arg(t_label_arg *new, t_asm *env);
void				add_label(t_label *new, t_asm *env);
int					is_label_char(char c);

/*
** parse_instructions.c
*/

int					parse_instructions(t_asm *env);

/*
** parsing.c
*/

int					start_parsing(t_header *header, t_asm *env);

/*
** tools.c
*/

int					check_space_digit(char *line, t_asm *env);
int					skip_whitespace(char *str, t_asm *env, int update);
int					skip_blank_lines(t_asm *env);
int					check_last_line(char *line, int option, t_asm *env);

/*
** write_cor_file.c
*/

void				write_cor_file(t_asm *env, t_header *header);

/*
** free_all.c
*/

int					free_all(t_asm *env);

/*
** op_fct functions
*/

int					ft_live(t_asm *env, int i, char *line);
int					ft_ld(t_asm *env, int i, char *line);
int					ft_st(t_asm *env, int i, char *line);
int					ft_add(t_asm *env, int i, char *line);
int					ft_sub(t_asm *env, int i, char *line);
int					ft_and(t_asm *env, int i, char *line);
int					ft_or(t_asm *env, int i, char *line);
int					ft_xor(t_asm *env, int i, char *line);
int					ft_zjmp(t_asm *env, int i, char *line);
int					ft_ldi(t_asm *env, int i, char *line);
int					ft_sti(t_asm *env, int i, char *line);
int					ft_fork(t_asm *env, int i, char *line);
int					ft_lld(t_asm *env, int i, char *line);
int					ft_lldi(t_asm *env, int i, char *line);
int					ft_lfork(t_asm *env, int i, char *line);
int					ft_aff(t_asm *env, int i, char *line);
int					fill_code(t_asm *env, int type, int value, int octet);
int					get_codage(t_arg arg);

static const t_op	g_op[] = {
	{"live", 4, ft_live},
	{"ldi", 3, ft_ldi},
	{"ld", 2, ft_ld},
	{"sti", 3, ft_sti},
	{"st", 2, ft_st},
	{"add", 3, ft_add},
	{"sub", 3, ft_sub},
	{"and", 3, ft_and},
	{"or", 2, ft_or},
	{"xor", 3, ft_xor},
	{"zjmp", 4, ft_zjmp},
	{"fork", 4, ft_fork},
	{"lldi", 4, ft_lldi},
	{"lld", 3, ft_lld},
	{"lfork", 5, ft_lfork},
	{"aff", 3, ft_aff}
};

#endif
