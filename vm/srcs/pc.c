/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:11:21 by adefonta          #+#    #+#             */
/*   Updated: 2019/07/13 13:51:31 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "macro.h"

static int	pc_index_base(int index_player, int nb_player)
{
	int	id;

	id = index_player * MEM_SIZE / nb_player;
	return (id);
}

void		pc_copy(t_pc *dest, t_pc *src)
{
	int	i;

	i = -1;
	while (++i < NB_REGISTRE)
		dest->reg[i] = src->reg[i];
	dest->carry = src->carry;
	dest->live = src->live;
}

int			pc_init_all(t_vm *vm, t_list **champi_lst)
{
	int		i;
	int		pc_index;
	t_list	*tmp;

	if (!vm->nb_champi)
		return (vm_usage());
	i = -1;
	while (++i < vm->nb_champi && champi_lst)
	{
		vm->last_living_champi = vm->champi[i];
		tmp = (*champi_lst)->next;
		pc_index = pc_index_base(i, vm->nb_champi);
		if (!init_pc(vm, vm->champi[i], pc_index))
			return (KO);
		ft_memcpy(&vm->arena[pc_index], (*champi_lst)->content,
									(*champi_lst)->content_size);
		arena_colors(vm, *vm->pc, pc_index, (*champi_lst)->content_size);
		ft_lstdelone2(champi_lst);
		*champi_lst = tmp;
	}
	if (i != vm->nb_champi || *champi_lst)
		return (error_int(ERROR_MALLOC));
	introduction(vm->champi);
	return (OK);
}

static void	remove_pc(t_vm *vm, t_pc **pre, t_pc **tmp)
{
	(vm->opt_v & 8) ? ft_printf(F_V8, (*tmp)->nb, vm->cycles_to_die) : 0;
	(*tmp)->champi->nb_process--;
	vm->nb_process--;
	if (*pre)
	{
		(*pre)->next = (*tmp)->next;
		free(*tmp);
		*tmp = (*pre)->next;
	}
	else
	{
		*pre = *tmp;
		*tmp = (*tmp)->next;
		vm->pc = *tmp;
		ft_memdel((void **)pre);
	}
}

int			pc_alive(t_vm *vm)
{
	t_pc	*pre;
	t_pc	*tmp;

	pre = NULL;
	tmp = vm->pc;
	while (tmp)
	{
		if (!tmp->live)
			remove_pc(vm, &pre, &tmp);
		else
		{
			tmp->live = 0;
			pre = tmp;
			tmp = pre->next;
		}
	}
	if (!vm->pc)
		return (KO);
	return (OK);
}
