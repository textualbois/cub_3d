/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_mmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:39:44 by isemin            #+#    #+#             */
/*   Updated: 2025/02/19 15:12:55 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	ft_mlx_highlight_pixel(uint8_t *pixel, uint32_t color)
{
	uint8_t		channels[4];
	uint32_t	new_color;
	int			i;

	channels[0] = (color >> 24) & 0xFF;
	channels[1] = (color >> 16) & 0xFF;
	channels[2] = (color >> 8) & 0xFF;
	channels[3] = color & 0xFF;
	i = 1;
	while (i < 4)
	{
		channels[i] = (uint8_t)fmin(255, channels[i] * 1.05);
		i++;
	}
	new_color = (channels[0] << 24) | (channels[1] << 16) | (channels[2] << 8) | channels[3];
	*(uint32_t *)pixel = new_color;
}

void	drawray(t_character *player, mlx_image_t *map_img, t_mini_map *mini_map,
		t_DoublePair hit)
{
	t_IntPair	start;
	t_IntPair	end;

	if (hit.x < 0 || hit.y < 0)
		return ;
	start.x = (player->pos.x - mini_map->view_port.x) / mini_map->visible_size.x
		* map_img->width;
	start.y = (player->pos.y - mini_map->view_port.y) / mini_map->visible_size.y
		* map_img->height;
	end.x = (hit.x - mini_map->view_port.x) / mini_map->visible_size.x
		* map_img->width;
	end.y = (hit.y - mini_map->view_port.y) / mini_map->visible_size.y
		* map_img->height;
	if (end.x >= 0 && end.y >= 0)
		highlight_line_between_pixels(map_img, start, end);
	draw_line_between_pixels(map_img, start, end, 0xFFFFFFFF);
}

void	draw_line_between_pixels(mlx_image_t *img, t_IntPair start,
		t_IntPair end, int color)
{
	t_IntPair	d;
	t_IntPair	direction;
	int			err;
	int			e2;

	d.y = -abs(end.y - start.y);
	d.x = abs(end.x - start.x);
	direction.y = start.y < end.y ? 1 : -1;
	direction.x = start.x < end.x ? 1 : -1;
	err = d.x + d.y;
	while (start.x != end.x || start.y != end.y)
	{
		if (start.x >= 0 && start.x < (int)img->width && start.y >= 0
			&& start.y < (int)img->height)
			mlx_put_pixel(img, start.x, start.y, color);
		e2 = 2 * err;
		if (e2 >= d.y)
		{
			err += d.y;
			start.x += direction.x;
		}
		if (e2 <= d.x)
		{
			err += d.x;
			start.y += direction.y;
		}
	}
}

void	highlight_line_between_pixels(mlx_image_t *img, t_IntPair start,
		t_IntPair end)
{
	t_IntPair	d;
	t_IntPair	direction;
	int			err;
	int			e2;
	uint8_t		*pixelstart;
	uint32_t	currentColor;

	d.y = -abs(end.y - start.y);
	d.x = abs(end.x - start.x);
	direction.y = start.y < end.y ? 1 : -1;
	direction.x = start.x < end.x ? 1 : -1;
	err = d.x + d.y;
	while (start.x != end.x || start.y != end.y)
	{
		if (start.x >= 0 && start.x < (int)img->width && start.y >= 0
			&& start.y < (int)img->height)
		{
			pixelstart = &img->pixels[(start.y * img->width + start.x) * BPP];
			currentColor = *(uint32_t *)pixelstart;
			ft_mlx_highlight_pixel(pixelstart, currentColor);
		}
		e2 = 2 * err;
		if (e2 >= d.y)
		{
			err += d.y;
			start.x += direction.x;
		}
		if (e2 <= d.x)
		{
			err += d.x;
			start.y += direction.y;
		}
	}
}
