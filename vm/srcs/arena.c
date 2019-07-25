/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:52:45 by adefonta          #+#    #+#             */
/*   Updated: 2019/03/07 21:58:41 by adefonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visu.h"

void		arena_colors(t_vm *vm, t_pc pc, unsigned int index, int jump)
{
	int	i;

	i = index;
	while (jump-- > 0)
	{
		i = i % MEM_SIZE;
		vm->arena_champi[i++] = pc.champi->index + 1;
	}
}

static int	read_pc(t_vm *vm)
{
	t_pc			*pc;

	pc = vm->pc;
	while (pc)
	{
		if (pc->count_down == 0)
		{
			if (pc->op_code == 0)
				op_define_type(pc, vm->arena[pc->index]);
			else if (pc->op_code != 0)
			{
				if (op_treat(vm, pc) == KO)
					return (KO);
			}
			pc->index %= MEM_SIZE;
		}
		else
			pc->count_down--;
		pc = pc->next;
	}
	return (OK);
}

static void	arena_init(t_vm *vm)
{
	vm->cycles = 1;
	vm->tot_cycles = 1;
	vm->cycles_to_die = CYCLE_TO_DIE;
}

int			arena_next_cycle(t_vm *vm)
{
	(vm->opt_v & 2) ? ft_printf("It is now cycle %d\n", vm->tot_cycles) : 0;
	if (vm->opt_dump != -1 && vm->opt_dump == vm->tot_cycles - 1)
		return (dump(vm));
	if (!read_pc(vm))
		return (KO);
	if (vm->cycles >= vm->cycles_to_die)
	{
		champi_reset_live(vm);
		if (pc_alive(vm) == KO)
			return (KO);
		if (++vm->checkups == MAX_CHECKS || vm->live_calls >= NBR_LIVE)
		{
			vm->cycles_to_die -= CYCLE_DELTA;
			(vm->opt_v & 2) ? ft_printf(F_V2, vm->cycles_to_die) : 0;
			vm->checkups = 0;
		}
		vm->cycles = 0;
		vm->live_calls = 0;
	}
	vm->cycles++;
	vm->tot_cycles++;
	return (OK);
}

int			arena_manage(t_vm *vm)
{
	t_param *p;

	p = NULL;
	arena_init(vm);
	if (vm->opt_g & 1)
	{
		if (!visu_init(p, vm))
			return (error_int(ERROR_VISU));
	}
	else
	{
		while (19)
		{
			if (arena_next_cycle(vm) == KO)
				return (OK);
		}
	}
	return (OK);
}
