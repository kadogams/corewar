/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbosity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadogam <skadogam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 11:39:45 by skadogam          #+#    #+#             */
/*   Updated: 2019/03/06 17:49:45 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "struct.h"

void	verbosity_4(t_pc pc, t_op op, int arg[3], char arg_type[3])
{
	int	i;

	i = -1;
	ft_printf("P %4d | %s", pc.nb, op.opcode);
	while (++i < op.nb_arg)
	{
		ft_printf(" ");
		if (arg_type[i] == REG_CODE)
			ft_printf("r");
		ft_printf("%d", arg[i]);
	}
	ft_printf("\n");
}

void	verbosity_16(t_pc pc, unsigned char *arena, int index, int len)
{
	if (index)
		ft_printf("ADV %d (%#.4x -> %#.4x) ", pc.arg_len + 1, index, len);
	else
		ft_printf("ADV %d (0x%.4x -> %#.4x) ", pc.arg_len + 1, index, len);
	while (index < len)
		ft_printf("%.2x ", arena[index++]);
	ft_printf("\n");
}
