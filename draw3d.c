/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:32:15 by isemin            #+#    #+#             */
/*   Updated: 2025/02/17 17:39:26 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include <stdio.h>

static uint32_t	get_pixel_color(mlx_texture_t *texture, uint32_t tex_x,
		uint32_t tex_y)
{
	uint8_t		*pixel;
	uint32_t	a;

	pixel = &texture->pixels[(texture->width * tex_y + tex_x) * BPP];
	a = pixel[3];
	if (a == 0)
		return (0x00000000);
	return ((pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3]);
}

static void	draw_texture_line(mlx_image_t *img, int row_ind, t_renderData *data,
		int x)
{
	double		t4w_ratio;
	t_IntPair	txtr_pix_whole;
	int			color;

	txtr_pix_whole.x = (int)data->txtr.x;
	t4w_ratio = (double)data->texture->height / (data->txtr_end
			- data->txtr_start);
	if (data->txtr_start < 0)
	{
		data->txtr.y = data->txtr.y + (-data->txtr_start * t4w_ratio);
	}
	while (row_ind < data->txtr_end && row_ind < (int)img->height)
	{
		txtr_pix_whole.y = (int)data->txtr.y;
		if (txtr_pix_whole.y >= (int)data->texture->height)
			txtr_pix_whole.y = data->texture->height - 1;
		color = get_pixel_color(data->texture, txtr_pix_whole.x,
				txtr_pix_whole.y);
		mlx_put_pixel(img, x, row_ind, color);
		row_ind++;
		data->txtr.y = data->txtr.y + t4w_ratio;
	}
}

static void	draw_vertical_line(mlx_image_t *img, t_renderData *data, int x)
{
	int	pix_y;

	pix_y = 0;
	if (data->txtr_start > (int)img->height)
		data->txtr_start = img->height;
	while (pix_y < data->txtr_start)
	{
		mlx_put_pixel(img, x, pix_y, 0xFF7220FF);
		pix_y++;
	}
	if (data->txtr_start < (int)img->height)
		draw_texture_line(img, pix_y, data, x);
	pix_y = data->txtr_end;
	while (pix_y < (int)img->height)
	{
		mlx_put_pixel(img, x, pix_y, 0xFF0220FF);
		pix_y++;
	}
}

void	draw3d(mlx_image_t *world3d, t_renderData *data, int x)
{
	double	dist_adjusted;
	double	lineH;
	double	vertical_offset;

	if (!world3d || !data)
	{
		//printf("[ERROR] draw3d: NULL pointer detected (world3d: %p, data: %p)\n", world3d, data);
		return ;
	}
	dist_adjusted = distance(data->hit, data->playerPos)
		* cos(normalise_radians(data->rayDir - data->playerDir.x));
	if (dist_adjusted < 0.001) // Защита от деления на ноль
		dist_adjusted = 0.001;
		
	lineH = TILE_SIZE * world3d->height / dist_adjusted;
	 if (lineH > 10000) // Ограничение высоты проекции
    	lineH = 10000;

	vertical_offset = (world3d->height / 2) * sin(data->playerDir.y);
	data->txtr_start = (world3d->height - lineH) / 2 + vertical_offset;
	// if (data->txtr_start < 0)
	// 	data->txtr_start = 0;

	data->txtr_end = (world3d->height + lineH) / 2 + vertical_offset;
	//  if (data->txtr_end > 1024)
	//  	data->txtr_end = 1024;
	printf("[DEBUG] draw3d: x=%d, dist_adjusted=%.6f, lineH=%.6f, vertical_offset=%.6f, txtr_start=%.6d, txtr_end=%.6d\n", x, dist_adjusted, lineH, vertical_offset, data->txtr_start, data->txtr_end);
	draw_vertical_line(world3d, data, x);
}
