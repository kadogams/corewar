/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:07:01 by adefonta          #+#    #+#             */
/*   Updated: 2019/07/13 13:34:20 by skadogam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "mlx.h"

static void	display_champi(t_mlx mlx, t_vm vm, int coord[2])
{
	int			i;
	char		*txt;
	t_champi	*champi;

	i = -1;
	txt = NULL;
	while (++i < vm.nb_champi)
	{
		champi = vm.champi[i];
		coord[1] += S_H;
		txt = ft_strjoin(T_PLAYER_NAME, champi->name);
		display_string(mlx, txt, coord, champi->color);
		txt = ft_strjoin_free(T_PLAYER_NUMBER, ft_itoa(champi->number), 1);
		display_string(mlx, txt, coord, champi->color);
		txt = ft_strjoin_free(T_PLAYER_LIVE, ft_itoa(champi->nb_live), 1);
		display_string(mlx, txt, coord, champi->color);
		txt = ft_strjoin_free(T_PLAYER_PROCESS, ft_itoa(champi->nb_process), 1);
		display_string(mlx, txt, coord, champi->color);
	}
}

static void	info_bottom(t_mlx mlx, t_vm vm, int coord[2])
{
	char	*txt;
	int		c;

	txt = NULL;
	c = C_WHITE;
	coord[1] += S_H;
	txt = ft_strjoin_free(T_CYCLE_TO_DIE, ft_itoa(vm.cycles_to_die), 1);
	display_string(mlx, txt, coord, c);
	txt = ft_strjoin_free(T_CYCLE_DELTA, ft_itoa(CYCLE_DELTA), 1);
	display_string(mlx, txt, coord, c);
	txt = ft_strjoin_free(T_NB_LIVE, ft_itoa(vm.live_calls), 1);
	display_string(mlx, txt, coord, c);
	txt = ft_strjoin_free(T_MAX_LIVE, ft_itoa(NBR_LIVE), 1);
	display_string(mlx, txt, coord, c);
	txt = ft_strjoin_free(T_NB_CHEKS, ft_itoa(vm.checkups), 1);
	display_string(mlx, txt, coord, c);
	txt = ft_strjoin_free(T_MAX_CHEKS, ft_itoa(MAX_CHECKS), 1);
	display_string(mlx, txt, coord, c);
	display_champi(mlx, vm, coord);
}

void		display_info(t_param p, t_mlx mlx, t_vm vm)
{
	int		coord[2];
	int		c;
	char	*txt;

	txt = NULL;
	c = C_WHITE;
	coord[1] = STRING_Y;
	coord[0] = STRING_X;
	txt = ft_strjoin_free(T_SPEED, ft_itoa(p.speed), 1);
	display_string(mlx, txt, coord, c);
	coord[1] += S_H;
	txt = ft_strjoin_free(T_CYCLE, ft_itoa(vm.cycles), 1);
	display_string(mlx, txt, coord, c);
	txt = ft_strjoin_free(T_CYCLE, ft_itoa(vm.tot_cycles), 1);
	display_string(mlx, txt, coord, c);
	txt = ft_strjoin_free(T_PLAYER, ft_itoa(vm.nb_champi), 1);
	display_string(mlx, txt, coord, c);
	txt = ft_strjoin_free(T_PROCESS, ft_itoa(vm.nb_process), 1);
	display_string(mlx, txt, coord, c);
	info_bottom(mlx, vm, coord);
}

void		display_cadre(t_img *img)
{
	int	x;
	int	y;
	int	arena_end[2];

	arena_end[0] = END_X + END_WIDTH;
	arena_end[1] = END_Y + END_HEIGHT;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = END_X / 2;
		while (x < WIN_WIDTH - ARENA_X / 2)
		{
			if (y > END_Y && y < arena_end[1] && x > END_X && x < arena_end[0])
				x = arena_end[0];
			else
			{
				img->data[coord_to_pos(x, y, WIN_WIDTH)] = C_RED;
				x += ((x % 5) == 0) ? 5 : 1;
			}
		}
		y += 5;
	}
}
