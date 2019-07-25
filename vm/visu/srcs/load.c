/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 21:37:27 by adefonta          #+#    #+#             */
/*   Updated: 2019/03/06 17:26:07 by adefonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "visu.h"
#include <pthread.h>

static double	percent_code(t_vm *vm, double memory[MAX_PLAYERS])
{
	int		i;
	double	tot;

	tot = 0;
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (vm->arena_champi[i] != 0)
		{
			memory[vm->arena_champi[i] - 1] += 1;
			tot += 1;
		}
	}
	return (tot);
}

static double	compute_lives(t_vm *vm)
{
	int		i;
	double	tot;

	tot = 0;
	i = -1;
	while (++i < vm->nb_champi)
		tot += vm->champi[i]->nb_live;
	return (tot);
}

static void		init(t_vm *vm, double tot[3], double tot_memory[MAX_PLAYERS])
{
	ft_bzero_double(tot_memory, MAX_PLAYERS);
	tot[0] = percent_code(vm, tot_memory);
	tot[1] = (double)vm->nb_process;
	tot[2] = compute_lives(vm);
}

static void		graph_data(t_vm *vm, t_graph *g)
{
	int				i;
	double			tot[3];
	double			tot_memory[MAX_PLAYERS];
	t_champi_graph	*champi;

	init(vm, tot, tot_memory);
	if (tot[0] || tot[1] || tot[2])
	{
		i = -1;
		while (++i < vm->nb_champi)
		{
			champi = g->champi[i];
			champi->code[g->index_fill] = (tot[0]) ? tot_memory[i] / tot[0] : 0;
			champi->process[g->index_fill] = (tot[1]) ?
							(double)vm->champi[i]->nb_process / tot[1] : 0;
			champi->lives[g->index_fill] = (tot[2]) ?
							(double)vm->champi[i]->nb_live / tot[2] : 0;
		}
		g->index_fill++;
		(g->is_full) ? g->index_display++ : 0;
		g->is_full = (!g->is_full && g->index_fill < GRAPH_NB_COLUMN) ? 0 : 1;
		g->index_display %= GRAPH_NB_COLUMN;
		g->index_fill %= GRAPH_NB_COLUMN;
	}
}

void			*load(void *arg)
{
	t_tdata *data;

	data = (t_tdata*)arg;
	if ((data->p->last_call + 20) < data->p->vm->tot_cycles)
	{
		graph_data(data->p->vm, data->p->graph);
		data->p->last_call = data->p->vm->tot_cycles;
	}
	graph_display(data->p, data->p->graph, data->img);
	if (data->p->mode_graph)
		graph_displaylive(data->p, data->p->graph, data->img);
	pthread_exit(NULL);
}
