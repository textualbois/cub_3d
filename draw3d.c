/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:32:15 by isemin            #+#    #+#             */
/*   Updated: 2025/02/12 21:21:19 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	draw_vertical_line(mlx_image_t *img, int start, int end, int x)
{
	int	i;
	int	color;

	i = 0;
	color = 0xFFF000FF;
	if (start < 0)
		start = 0 ;
	if (end > (int)img->height)
	{
		end = img->height;
	}
	while (i < start)
	{
		mlx_put_pixel(img, x, i, 0xFF7220FF);
		i++;
	}
	while (i < end)
	{
		mlx_put_pixel(img, x, i, color);
		i++;
	}

	while (i < (int)img->height)
	{
		mlx_put_pixel(img, x, i, 0xFF0220FF);
		i++;
	}
		mlx_put_pixel(img, x, start, 0xFFFFFFFF);
		mlx_put_pixel(img, x, end - 1, 0xFFFFFFFF);
}

void	draw3d(mlx_image_t *world3d, double distance, double rad_delta, int x)
{
	// t_IntPair window_size;
	// (void)rad_delta;
	distance *= cos(rad_delta);
	double lineH = TILE_SIZE * world3d->height / distance;
	// int mid = world3d->height / 2;
	draw_vertical_line(world3d, (world3d->height - lineH) / 2, (world3d->height + lineH) / 2, x);
}
