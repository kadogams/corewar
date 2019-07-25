/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 22:14:10 by adefonta          #+#    #+#             */
/*   Updated: 2019/03/12 19:26:39 by adefonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "visu_struct.h"
#include "vm.h"

static void	free_graph(t_param *p)
{
	int	i;

	i = -1;
	while (++i < p->vm->nb_champi)
		free(p->graph->champi[i]);
	free(p->graph);
}

static void	free_vm(t_param *p)
{
	free_champi_list(p->vm->champi, p->vm->nb_champi);
	free_pc_list(p->vm->pc);
}

void		free_image(t_param *param, t_img *img)
{
	if (img)
	{
		mlx_destroy_image(param->mlx->ptr, img->ptr);
		free(img);
	}
}

void		del_param(t_param *param)
{
	t_mlx	*mlx;

	if (param)
	{
		param->run = 0;
		and_the_winner_is(param->vm, param->vm->last_living_champi);
		free_graph(param);
		free_vm(param);
		if ((mlx = param->mlx))
		{
			free_image(param, param->img);
			if (mlx->ptr && mlx->win)
			{
				mlx_clear_window(mlx->ptr, mlx->win);
				mlx_destroy_window(mlx->ptr, mlx->win);
				free(mlx->ptr);
			}
			free(mlx);
		}
		free(param);
	}
	exit(0);
}
