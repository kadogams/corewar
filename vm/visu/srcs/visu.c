/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:52:31 by adefonta          #+#    #+#             */
/*   Updated: 2019/03/12 17:29:34 by adefonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "visu_macro.h"
#include "macro.h"
#include "mlx.h"
#include "keycode.h"
#include "vm.h"

static int		init_param(t_param **param, char *title, int width, int height)
{
	if (!((*param) = (t_param *)ft_memalloc(sizeof(t_param))))
		return (KO);
	if (!((*param)->mlx = mlx_init_window(width, height, title)))
	{
		free(*param);
		return (KO);
	}
	(*param)->speed = 10;
	return (OK);
}

int				visu_init(t_param *p, t_vm *vm)
{
	if (init_param(&p, T_WIN, WIN_WIDTH, WIN_HEIGHT) == KO)
		return (KO);
	p->vm = vm;
	graph_init(p, p->vm);
	visu_print(p);
	mlx_hook(p->mlx->win, KEYPRESS, KPMASK, event_keyboard, p);
	mlx_loop_hook(p->mlx->ptr, event_loop, p);
	mlx_loop(p->mlx->ptr);
	del_param(p);
	return (OK);
}

static t_img	*new_map(t_mlx *mlx, int width, int height)
{
	t_img	*img;
	int		len[2];

	len[0] = width;
	len[1] = height;
	if (!(img = img_create(mlx, len)))
		return (NULL);
	return (img);
}

void			visu_print(t_param *p)
{
	t_img	*img;

	if ((img = new_map(p->mlx, WIN_WIDTH, WIN_HEIGHT)))
	{
		graph(p, img);
		if (!(p->mode_graph))
			display_pcbg(p->vm, img);
		mlx_put_image_to_window(p->mlx->ptr, p->mlx->win, img->ptr, 0, 0);
		free_image(p, img);
		if (!(p->mode_graph))
			display_arena(p);
		display_graphtitle(p->mlx, p->graph, p->mode_graph);
	}
	display_info(*p, *p->mlx, *p->vm);
}

void			visu_ending(t_param *p)
{
	t_img	*img;

	p->end = 1;
	p->run = 0;
	if ((img = new_map(p->mlx, WIN_WIDTH, WIN_HEIGHT)))
	{
		display_cadre(img);
		mlx_put_image_to_window(p->mlx->ptr, p->mlx->win, img->ptr, 0, 0);
		free_image(p, img);
		display_end(p->mlx, p->vm);
		display_info(*p, *p->mlx, *p->vm);
	}
}
