/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 19:20:38 by adefonta          #+#    #+#             */
/*   Updated: 2019/03/06 14:48:11 by adefonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "keycode.h"
#include "vm.h"
#include "mlx.h"

int		event_loop(t_param *p)
{
	if (p->run)
	{
		if (arena_next_cycle(p->vm) == KO)
			visu_ending(p);
		else if ((p->vm->cycles % p->speed) == 0)
			visu_print(p);
	}
	else
		usleep(150000);
	return (OK);
}

int		event_keyboard(int key, t_param *p)
{
	if (key == SP_KEY && !p->end)
		p->run = !p->run;
	if (key == ESC_KEY)
		del_param(p);
	else
	{
		if (key == NKMN_KEY && p->speed > SPEED_MIN)
			p->speed--;
		if (key == NKPL_KEY && p->speed < SPEED_MAX)
			p->speed++;
		if (key == G_KEY)
		{
			p->mode_graph = !(p->mode_graph);
			graph_resize(p->graph, p->mode_graph);
		}
		if (key == M_KEY)
		{
			p->graph->mode++;
			p->graph->mode %= 3;
		}
		if (p->run == 0 && !p->end)
			visu_print(p);
	}
	return (OK);
}
