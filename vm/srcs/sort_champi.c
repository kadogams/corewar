/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_champi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 11:25:46 by skadogam          #+#    #+#             */
/*   Updated: 2019/07/13 14:19:06 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	swap_int(int *x, int *y)
{
	int	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

static void	swap_champi(t_champi **a, t_champi **b)
{
	t_champi	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
	swap_int(&(*a)->index, &(*b)->index);
	swap_int(&(*a)->color, &(*b)->color);
}

static void	swap_list_contents(t_list **x, t_list **y)
{
	void	*tmp_content;
	size_t	tmp_size;

	tmp_content = (*x)->content;
	(*x)->content = (*y)->content;
	(*y)->content = tmp_content;
	tmp_size = (*x)->content_size;
	(*x)->content_size = (*y)->content_size;
	(*y)->content_size = tmp_size;
}

void		sort_champi_by_number(t_vm *vm, t_list **champi_lst)
{
	int			i;
	int			j;
	t_list		*head;
	t_list		*tmp;

	i = 0;
	head = *champi_lst;
	while (i < vm->nb_champi && champi_lst)
	{
		j = i;
		tmp = *champi_lst;
		while (++j < vm->nb_champi && (tmp = tmp->next))
		{
			if (vm->champi[i]->number < vm->champi[j]->number)
			{
				swap_champi(&vm->champi[i], &vm->champi[j]);
				swap_list_contents(champi_lst, &tmp);
			}
		}
		i++;
		*champi_lst = (*champi_lst)->next;
	}
	*champi_lst = head;
}
