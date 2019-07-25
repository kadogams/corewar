/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 14:14:34 by adefonta          #+#    #+#             */
/*   Updated: 2019/07/13 13:34:56 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "mlx.h"

void		display_graphtitle(t_mlx *mlx, t_graph *g, int mode_graph)
{
	char	*txt;
	int		x;
	int		y;
	int		c;

	c = C_WHITE;
	if (mode_graph)
	{
		x = g->org[0] + g->dim[0] / 2 + GRAPH_SPACE;
		y = g->org[1] - (2 * S_H);
		mlx_string_put(mlx->ptr, mlx->win, g->org[0], y, c, GRAPH_TITLE_1);
		mlx_string_put(mlx->ptr, mlx->win, x, y, c, GRAPH_TITLE_2);
		x = g->org[0];
		y = GRAPH_LIVE_Y - (2 * S_H);
		mlx_string_put(mlx->ptr, mlx->win, x, y, c, GRAPH_TITLE_3);
	}
	else
	{
		if (g->mode != 2)
			txt = (g->mode) ? GRAPH_TITLE_2 : GRAPH_TITLE_1;
		else
			txt = GRAPH_TITLE_3;
		y = g->org[1] - (2 * S_H);
		mlx_string_put(mlx->ptr, mlx->win, g->org[0], y, c, txt);
	}
}

void		display_pcbg(t_vm *vm, t_img *img)
{
	t_pc	*tmp;
	int		index;
	int		coord[2];
	int		len[2];

	len[0] = S_W * 0.70;
	len[1] = S_H * 0.90;
	tmp = vm->pc;
	while (tmp)
	{
		index = tmp->index % MEM_SIZE;
		coord[0] = ARENA_X + (index % 64) * S_W;
		coord[1] = ARENA_Y + (index / 64) * S_H + 2;
		color_image(*img, coord, len, tmp->champi->color);
		if (tmp->pre_index != tmp->index)
		{
			index = tmp->pre_index % MEM_SIZE;
			coord[0] = ARENA_X + (index % 64) * S_W;
			coord[1] = ARENA_Y + (index / 64) * S_H + 2;
			color_image(*img, coord, len, 0x000000);
		}
		tmp->pre_index = tmp->index;
		tmp = tmp->next;
	}
}

void		display_arena(t_param *p)
{
	int		j;
	int		c[2];
	int		color;
	char	*hex;
	char	print[3];

	c[1] = ARENA_Y;
	c[0] = ARENA_X;
	j = -1;
	print[2] = '\0';
	while (++j < MEM_SIZE)
	{
		c[0] = (j && !(j % 64)) ? ARENA_X : c[0];
		c[1] += (j && !(j % 64)) ? S_H : 0;
		if ((hex = ft_utoa_base((unsigned int)p->vm->arena[j], 16, 0)))
		{
			print[0] = (hex[1] != '\0') ? hex[0] : '0';
			print[1] = (hex[1] == '\0') ? hex[0] : hex[1];
			color = (p->vm->arena_champi[j]) ?
					p->vm->champi[p->vm->arena_champi[j] - 1]->color : C_WHITE;
			mlx_string_put(p->mlx->ptr, p->mlx->win, c[0], c[1], color, print);
			free(hex);
		}
		c[0] += S_W;
	}
}

static void	display_champi(t_mlx *mlx, t_vm vm, int coord[2])
{
	int			i;
	char		*txt;
	t_champi	*c;

	i = -1;
	txt = NULL;
	while (++i < vm.nb_champi)
	{
		c = vm.champi[i];
		coord[1] += S_H;
		txt = ft_strjoin(T_PLAYER_NAME, c->name);
		if (vm.last_living_champi != NULL && vm.last_living_champi->index == i)
			txt = ft_strjoin_free(txt, " is the WINNER!", 0);
		display_string(*mlx, txt, coord, c->color);
		txt = ft_strjoin_free(T_PLAYER_NUMBER, ft_itoa(c->number), 1);
		display_string(*mlx, txt, coord, c->color);
		txt = ft_strjoin_free(T_PLAYER_DEATH_CYCLE, ft_itoa(c->last_live), 1);
		display_string(*mlx, txt, coord, c->color);
	}
}

void		display_end(t_mlx *mlx, t_vm *vm)
{
	int		coord[2];
	int		c;

	c = C_WHITE;
	coord[1] = STRING_END_Y;
	coord[0] = STRING_END_X;
	mlx_string_put(mlx->ptr, mlx->win, coord[0], coord[1], c, T_END);
	coord[1] += 2 * S_H;
	display_champi(mlx, *vm, coord);
}
