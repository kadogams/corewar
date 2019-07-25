/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 16:58:41 by adefonta          #+#    #+#             */
/*   Updated: 2019/07/13 14:21:40 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visu.h"
#include "macro.h"
#include "visu_macro.h"

static void	champi_set_number(t_vm *vm, t_champi *current, long number)
{
	int	i;
	int	new_number;

	if (number != NB_OK)
	{
		i = -1;
		while (vm->champi[++i] && vm->champi[i]->number != number)
			;
		if (!vm->champi[i])
		{
			current->number = (int)number;
			return ;
		}
	}
	new_number = -1;
	i = -1;
	while (vm->champi[++i])
	{
		if (vm->champi[i]->number == new_number)
			new_number--;
	}
	current->number = new_number;
}

t_champi	*champi_init(t_vm *vm, int index, long number)
{
	t_champi	*champi;

	if (++vm->nb_champi > MAX_PLAYERS)
		return (error_null(ERROR_CHAMPI_TOOMANY));
	if (!(champi = (t_champi *)ft_memalloc(sizeof(t_champi))))
		return (error_null(ERROR_CHAMPI_NULL));
	champi->index = index;
	champi->color = g_colors[index];
	champi->nb_process = 1;
	champi->nb_live = 0;
	champi_set_number(vm, champi, number);
	vm->champi[index] = champi;
	vm->nb_process++;
	return (champi);
}

int			champi_reset_live(t_vm *vm)
{
	int	i;
	int	state;

	state = KO;
	i = -1;
	while (++i < vm->nb_champi)
	{
		(vm->champi[i]->nb_live > 0) ? state = OK : 0;
		vm->champi[i]->nb_live = 0;
	}
	return (state);
}
