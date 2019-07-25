/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:10:15 by adefonta          #+#    #+#             */
/*   Updated: 2019/03/06 17:56:10 by adefonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "visu.h"
#include <pthread.h>

static int	define_next_step(t_graph *graph, int *index, int column, int mode)
{
	int		index_hist;
	double	percent;

	percent = 0;
	index_hist = (column + graph->index_display) % GRAPH_NB_COLUMN;
	*index += 1;
	if (mode == 0)
		percent = graph->champi[*index]->code[index_hist] * graph->dim[1];
	else if (mode == 1)
		percent = graph->champi[*index]->process[index_hist] * graph->dim[1];
	else if (mode == 2)
		percent = graph->champi[*index]->lives[index_hist] * graph->dim[1];
	else if (mode == 3)
		percent = graph->champi[*index]->lives[index_hist] * GRAPH_LIVE_HEIGHT;
	return (percent);
}

static void	data_in_img(t_param *p, t_img *img, int pos[3], int ichamp[2])
{
	int	i;

	i = -1;
	while (++i < p->graph->column_size)
	{
		img->data[coord_to_pos(pos[0] + i, pos[2], WIN_WIDTH)] =
							p->vm->champi[ichamp[0]]->color;
		if (p->mode_graph)
			img->data[coord_to_pos(pos[1] + i, pos[2], WIN_WIDTH)] =
								p->vm->champi[ichamp[1]]->color;
		i += p->graph->pixel_jump;
	}
}

static void	define_data(t_param *p, int pos[4], int ichamp[2], int nchamp[2])
{
	if (p->mode_graph)
	{
		if (nchamp[0] <= pos[2] && ichamp[0] + 1 < p->vm->nb_champi)
			nchamp[0] += define_next_step(p->graph, &ichamp[0], pos[3], 0);
		if (nchamp[1] <= pos[2] && ichamp[1] + 1 < p->vm->nb_champi)
			nchamp[1] += define_next_step(p->graph, &ichamp[1], pos[3], 1);
	}
	else
	{
		if (nchamp[0] <= pos[2] && ichamp[0] + 1 < p->vm->nb_champi)
			nchamp[0] +=
				define_next_step(p->graph, &ichamp[0], pos[3], p->graph->mode);
	}
}

void		graph_display(t_param *p, t_graph *g, t_img *img)
{
	int	ichamp[2];
	int	nchamp[2];
	int	pos[4];

	pos[3] = -1;
	while (++pos[3] < ((g->is_full) ? GRAPH_NB_COLUMN : g->index_fill))
	{
		pos[2] = g->org[1] - 1;
		nchamp[0] = g->org[1];
		nchamp[1] = g->org[1];
		ichamp[0] = -1;
		ichamp[1] = -1;
		while (++pos[2] < g->org[1] + g->dim[1])
		{
			define_data(p, pos, ichamp, nchamp);
			pos[0] = g->org[0] + pos[3] * g->column_size;
			pos[1] = pos[0] + g->dim[0] / 2 + GRAPH_SPACE;
			data_in_img(p, img, pos, ichamp);
			pos[2] += g->pixel_jump;
		}
	}
}

void		graph_displaylive(t_param *p, t_graph *g, t_img *img)
{
	int data[3];
	int	pos[2];
	int	i;

	data[0] = -1;
	while (++data[0] < ((g->is_full) ? GRAPH_NB_COLUMN : g->index_fill))
	{
		pos[1] = GRAPH_LIVE_Y - 1;
		data[2] = GRAPH_LIVE_Y;
		data[1] = -1;
		while (++pos[1] < GRAPH_LIVE_Y + GRAPH_LIVE_HEIGHT)
		{
			if (data[2] <= pos[1] && data[1] + 1 < p->vm->nb_champi)
				data[2] += define_next_step(g, &data[1], data[0], 3);
			pos[0] = GRAPH_X + data[0] * GRAPH_LIVE_COLUMN;
			i = -1;
			while (++i < GRAPH_LIVE_COLUMN)
			{
				img->data[coord_to_pos(pos[0] + i, pos[1], WIN_WIDTH)] =
										p->vm->champi[data[1]]->color;
				i += 3;
			}
			pos[1] += 3;
		}
	}
}
