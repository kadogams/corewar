/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 23:35:41 by adefonta          #+#    #+#             */
/*   Updated: 2019/03/12 17:30:42 by adefonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "mlx.h"
#include "visu_macro.h"

int		img_color_bg(t_img *img, int start, int end, int color)
{
	while (start < end)
	{
		color_at_pos(*img, start, color);
		start++;
	}
	return (OK);
}

t_img	*img_create(t_mlx *mlx, int dim[2])
{
	t_img	*image;

	if (!(image = (t_img *)malloc(sizeof(t_img))))
		return (NULL);
	image->dim[0] = dim[0];
	image->dim[1] = dim[1];
	image->ptr = mlx_new_image(mlx->ptr, image->dim[0], image->dim[1]);
	image->data = (int *)mlx_get_data_addr(image->ptr,
			&image->opp, &image->sizeline, &image->endian);
	image->opp /= 8;
	image->size = image->dim[0] * image->dim[1];
	if (!image->ptr || !image->data)
	{
		free(image);
		return (NULL);
	}
	return (image);
}
