/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:58:48 by skadogam          #+#    #+#             */
/*   Updated: 2019/07/13 11:44:23 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	init_put_colors(void (*put[7])(int n))
{
	put[0] = put_neutral;
	put[1] = put_red;
	put[2] = put_blue;
	put[3] = put_green;
	put[4] = put_yellow;
	put[5] = put_cyan;
	put[6] = put_mauve;
}

static void	print_char(unsigned char *arena, int i)
{
	int	count;

	count = 16;
	ft_printf("  |");
	while (i < MEM_SIZE && count--)
	{
		if (ft_isprint(arena[i]))
			ft_printf("%c", arena[i]);
		else
			ft_printf(".");
		i++;
	}
	ft_printf("|");
}

static int	skip_empty_lines(t_vm *vm, int *blank, int *i, int skip)
{
	if (*i + 16 < MEM_SIZE &&
		!ft_memcmp(&vm->arena_champi[*i], blank, 16 * sizeof(int)))
	{
		if (skip == OK)
		{
			print_char(vm->arena, *i - 16);
			ft_printf("\n*");
			*i += 16;
			while (*i + 16 < MEM_SIZE &&
				!ft_memcmp(&vm->arena_champi[*i], blank, 16 * sizeof(int)))
				*i += 16;
			return (KO);
		}
		print_char(vm->arena, *i - 16);
		return (OK);
	}
	print_char(vm->arena, *i - 16);
	return (KO);
}

int			dump(t_vm *vm)
{
	int		i;
	int		skip;
	int		blank[16];
	void	(*put_colors[7])(int n);

	i = -1;
	skip = 0;
	ft_bzero(blank, 16 * sizeof(int));
	init_put_colors(put_colors);
	ft_printf("0x0000 : ");
	while (++i < MEM_SIZE)
	{
		if (i && !(i % 16))
		{
			skip = skip_empty_lines(vm, blank, &i, skip);
			ft_printf("\n%#.4x : ", i);
		}
		else if (i && !(i % 8))
			ft_printf(" ");
		put_colors[vm->arena_champi[i]](vm->arena[i]);
	}
	print_char(vm->arena, i - 16);
	ft_printf("\n");
	vm->last_living_champi = NULL;
	return (KO);
}
