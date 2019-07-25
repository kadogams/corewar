/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:13:00 by adefonta          #+#    #+#             */
/*   Updated: 2019/02/20 13:57:52 by adefonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_STRUCT_H
# define VISU_STRUCT_H

# include "visu_macro.h"
# include "struct.h"
# include "macro.h"

typedef struct	s_champi_graph
{
	double	code[GRAPH_NB_COLUMN];
	double	process[GRAPH_NB_COLUMN];
	double	lives[GRAPH_NB_COLUMN];

}				t_champi_graph;

typedef struct	s_graph
{
	int				mode;
	int				dim[2];
	int				org[2];
	int				column_size;
	int				pixel_jump;
	int				index_display;
	int				index_fill;
	int				is_full;
	t_champi_graph	*champi[MAX_PLAYERS];
}				t_graph;

typedef struct	s_img
{
	int		index;
	int		win_pos[2];
	int		dim[2];
	int		sizeline;
	int		size;
	int		endian;
	int		opp;
	int		start;
	int		org[2];
	void	*ptr;
	int		*data;
}				t_img;

typedef struct	s_mlx
{

	int		dim[2];
	int		color;
	void	*ptr;
	void	*win;
}				t_mlx;

typedef struct	s_param
{

	int				press;
	int				ready;
	int				m_color;
	int				i_color;
	int				b_mode;
	int				run;
	int				end;
	int				colors[3];
	int				speed;
	int				last_call;
	int				mode_graph;
	t_graph			*graph;
	t_mlx			*mlx;
	t_img			*img;
	t_vm			*vm;
}				t_param;

typedef struct	s_tdata
{
	t_param	*p;
	t_img	*img;
}				t_tdata;

#endif
