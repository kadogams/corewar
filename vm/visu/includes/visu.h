/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:54:20 by adefonta          #+#    #+#             */
/*   Updated: 2019/03/12 17:22:25 by adefonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include "visu_struct.h"
# include "libftprintf.h"
# include "visu_macro.h"

int			visu_init(t_param *p, t_vm *vm);
void		visu_print(t_param *p);
void		visu_ending(t_param *p);

void		del_param(t_param *param);
void		free_image(t_param *param, t_img *img);

int			img_color_bg(t_img *img, int start, int end, int color);
t_img		*img_create(t_mlx *mlx, int dim[2]);

int			event_loop(t_param *p);
int			event_keyboard(int key, t_param *p);

t_mlx		*mlx_init_window(int width, int height, char *title);

void		color_image(t_img img, int coord[2], int len[2], int color);
int			color_at_pos(t_img img, int pos, int color);

char		*strint(char *base, int data);
char		*ft_strjoin_free(char *s1, char *s2, int i_free);
int			coord_to_pos(int x, int y, int width);
void		ft_bzero_double(double *s, size_t n);

void		display_arena(t_param *p);
void		display_graphtitle(t_mlx *mlx, t_graph *g, int mode_graph);
void		display_pcbg(t_vm *vm, t_img *img);
void		display_end(t_mlx *mlx, t_vm *vm);

void		display_info(t_param param, t_mlx mlx, t_vm vm);
void		display_cadre(t_img *img);

void		display_string(t_mlx mlx, char *line, int coord[2], int color);

int			graph_init(t_param *p, t_vm *vm);
void		graph_resize(t_graph *graph, int is_full);
void		graph(t_param *p, t_img *img);

void		graph_displaylive(t_param *p, t_graph *g, t_img *img);
void		graph_display(t_param *p, t_graph *g, t_img *img);

void		*load(void *arg);

static const int	g_colors[MAX_PLAYERS] = {
	C_RED, C_BLUE, C_GREEN, C_YELLOW, C_CYAN, C_MAUVE
};

#endif
