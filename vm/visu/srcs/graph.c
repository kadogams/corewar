/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 20:28:25 by adefonta          #+#    #+#             */
/*   Updated: 2019/03/06 17:56:50 by adefonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "visu.h"
#include <pthread.h>

int		graph_init(t_param *p, t_vm *vm)
{
	int				i;
	t_champi_graph	*champi;

	if (!(p->graph = (t_graph*)ft_memalloc(sizeof(t_graph))))
		return (KO);
	i = -1;
	while (++i < vm->nb_champi)
	{
		if (!(champi = (t_champi_graph*)ft_memalloc(sizeof(t_champi_graph))))
			return (KO);
		p->graph->champi[i] = champi;
	}
	graph_resize(p->graph, 0);
	return (OK);
}

void	graph_resize(t_graph *graph, int is_full)
{
	if (is_full)
	{
		graph->dim[0] = GRAPH_WIDTH;
		graph->dim[1] = GRAPH_HEIGHT;
		graph->org[0] = GRAPH_X;
		graph->org[1] = GRAPH_Y;
		graph->column_size = GRAPH_COLUMN;
		graph->pixel_jump = 3;
	}
	else
	{
		graph->dim[0] = GRAPH_MINI_WIDTH;
		graph->dim[1] = GRAPH_MINI_HEIGHT;
		graph->org[0] = GRAPH_MINI_X;
		graph->org[1] = GRAPH_MINI_Y;
		graph->column_size = GRAPH_MINI_COLUMN;
		graph->pixel_jump = 1;
	}
}

void	graph(t_param *p, t_img *img)
{
	t_tdata		data;
	pthread_t	thread;

	data.p = p;
	data.img = img;
	pthread_create(&thread, NULL, load, &data);
	pthread_join(thread, NULL);
}
