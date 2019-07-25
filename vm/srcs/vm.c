/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 11:09:56 by skadogam          #+#    #+#             */
/*   Updated: 2019/07/13 13:47:25 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		and_the_winner_is(t_vm *vm, t_champi *winner)
{
	if (!winner)
		return ;
	ft_printf("Player %d (%s) won !\n", winner->number,
		winner->name);
	if (vm->opt_dump != -1)
		dump(vm);
}

int			vm_usage(void)
{
	ft_putendl_fd("Usage: ./corewar [-a] [-dump N -v N] [-g] "
	"[-n N] <champion1.cor> [-n N] <...>\n"
	"\t-a\t  : Prints output from \"aff\" (Default is to hide it)\n"
	"\t-n N\t  : Sets the number of the next player\n"
	"#### TEXT OUTPUT MODE "
	"##########################################################\n"
	"\t-dump N   : Dumps memory after N cycles then exits\n"
	"\t-v N\t  : Verbosity levels, can be added together to enable several\n"
	"\t\t    - 0 : Show only essentials\n"
	"\t\t    - 1 : Show lives\n"
	"\t\t    - 2 : Show cycles\n"
	"\t\t    - 4 : Show operations (Params are NOT litteral ...)\n"
	"\t\t    - 8 : Show deaths\n"
	"\t\t    - 16 : Show PC movements (Except for jumps)\n"
	"#### GRAPHICAL OUTPUT MODE "
	"#####################################################\n"
	"\t-g\t  : Graphical output mode for corewar", 2);
	return (0);
}

int			main(int ac, char **av)
{
	t_list	*champi_lst;
	t_vm	vm;

	champi_lst = NULL;
	if (ac == 1)
		vm_usage();
	else
	{
		init_vm(&vm);
		if (parse_champi(&vm, ac, av, &champi_lst))
		{
			if (arena_manage(&vm))
				and_the_winner_is(&vm, vm.last_living_champi);
		}
		else
			ft_lstdel2(&champi_lst);
		free_champi_list(vm.champi, vm.nb_champi);
		free_pc_list(vm.pc);
	}
	return (0);
}
