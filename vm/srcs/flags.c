/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadogams <kadogams@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 03:49:19 by kadogams          #+#    #+#             */
/*   Updated: 2019/03/09 08:27:27 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"

static int	get_number(int ac, char **av, int *i, long *n)
{
	if (*i + 3 >= ac)
		return (KO);
	*n = (long)ft_atoi(av[*i + 2]);
	*i += 2;
	return (OK);
}

static int	get_dump(int ac, char **av, int *i, int *n)
{
	if (*i + 2 >= ac)
		return (KO);
	*n = ft_atoi(av[*i + 2]);
	if (*n < 0)
		*n = 0;
	*i += 2;
	return (OK);
}

static int	get_verbosity(int ac, char **av, int *i, char *verbosity)
{
	int	tmp;

	if (*i + 2 >= ac)
		return (KO);
	*verbosity = 0;
	tmp = ft_atoi(av[*i + 2]);
	*verbosity |= tmp;
	*i += 2;
	return (OK);
}

long		flags_get(t_vm *vm, int ac, char **av, int *i)
{
	long	number;

	if (*i + 1 >= ac || *av[*i + 1] != '-')
		return (NB_OK);
	if (ft_strequ(av[*i + 1], "-n") && get_number(ac, av, i, &number))
		return (number);
	else if (ft_strequ(av[*i + 1], "-dump") &&
				get_dump(ac, av, i, &vm->opt_dump))
		return (flags_get(vm, ac, av, i));
	else if (ft_strequ(av[*i + 1], "-v") &&
				get_verbosity(ac, av, i, &vm->opt_v))
		return (flags_get(vm, ac, av, i));
	else if (ft_strequ(av[*i + 1], "-a"))
	{
		vm->opt_aff |= 1;
		*i += 1;
		return (flags_get(vm, ac, av, i));
	}
	else if (ft_strequ(av[*i + 1], "-g"))
	{
		vm->opt_g |= 1;
		*i += 1;
		return (flags_get(vm, ac, av, i));
	}
	return (NB_OK);
}
