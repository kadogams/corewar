/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 19:00:47 by adefonta          #+#    #+#             */
/*   Updated: 2019/03/12 17:31:23 by adefonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "macro.h"
#include "libftprintf.h"
#include <stdlib.h>

void	free_pc_list(t_pc *pc)
{
	t_pc	*tmp;

	if (!pc)
		return ;
	while (pc)
	{
		tmp = pc->next;
		free(pc);
		pc = tmp;
	}
}

void	free_champi_list(t_champi *champis[MAX_PLAYERS], int nb_player)
{
	int	i;

	i = -1;
	if (!champis)
		return ;
	while (++i < nb_player)
	{
		if (champis[i])
		{
			free(champis[i]->name);
			free(champis[i]->cmt);
		}
		free(champis[i]);
	}
}
