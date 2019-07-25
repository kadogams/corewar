/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:52:13 by adefonta          #+#    #+#             */
/*   Updated: 2019/02/20 14:26:00 by adefonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "mlx.h"

void	display_string(t_mlx mlx, char *line, int coord[2], int color)
{
	coord[1] += S_H;
	if (line)
	{
		mlx_string_put(mlx.ptr, mlx.win, coord[0], coord[1], color, line);
		free(line);
	}
}
