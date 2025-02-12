/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:32:15 by isemin            #+#    #+#             */
/*   Updated: 2025/02/12 20:06:06 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	draw_vertical_line(mlx_image_t *img, int start, int end, int x)
{
	int	i;
	int	color;

	i = 0;
	color = 0xFFF0004F;
	if (start + i < 0)
		start = 0 - i;
	if (end > (int)img->height)
		end = img->height;
	while (start + i < end)
	{
		mlx_put_pixel(img, x, start+i, color);
		i++;
	}
	while (start + i < (int)img->height)
	{
		mlx_put_pixel(img, x, start+i, 0xFF022011);
		i++;
	}
}

void	draw3d(mlx_image_t *world3d, double distance, double rayDir, int x)
{
	// t_IntPair window_size;
	(void)rayDir;
	double lineH = TILE_SIZE * world3d->height / distance;
	draw_vertical_line(world3d, (world3d->width - lineH) / 2, (world3d->width + lineH) / 2, x);
}
