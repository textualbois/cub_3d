/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_mmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:39:44 by isemin            #+#    #+#             */
/*   Updated: 2025/02/22 19:50:21 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	ft_mlx_highlight_pixel(uint8_t *pixel, uint32_t color)
{
	uint8_t		chan[4];
	uint32_t	new_color;
	int			i;

	chan[0] = (color >> 24) & 0xFF;
	chan[1] = (color >> 16) & 0xFF;
	chan[2] = (color >> 8) & 0xFF;
	chan[3] = color & 0xFF;
	i = 1;
	while (i < 4)
	{
		chan[i] = (uint8_t)fmin(255, chan[i] * 1.05);
		i++;
	}
	new_color = (chan[0] << 24) | (chan[1] << 16) | (chan[2] << 8) | chan[3];
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
	highlight_line_between_pixels(map_img, start, end);
}

void	draw_line_step(t_IntPair *start, t_IntPair direction, t_IntPair d,
		int *err)
{
	int	e2;

	e2 = 2 * (*err);
	if (e2 >= d.y)
	{
		*err += d.y;
		start->x += direction.x;
	}
	if (e2 <= d.x)
	{
		*err += d.x;
		start->y += direction.y;
	}
}

void	draw_line_between_pixels(mlx_image_t *img, t_IntPair start,
		t_IntPair end, int color)
{
	t_IntPair	d;
	t_IntPair	direction;
	int			err;

	d.y = -abs(end.y - start.y);
	d.x = abs(end.x - start.x);
	if (start.y < end.y)
		direction.y = 1;
	else
		direction.y = -1;
	if (start.x < end.x)
		direction.x = 1;
	else
		direction.x = -1;
	err = d.x + d.y;
	while (start.x != end.x || start.y != end.y)
	{
		if (start.x >= 0 && start.x < (int)img->width && start.y >= 0
			&& start.y < (int)img->height)
			mlx_put_pixel(img, start.x, start.y, color);
		draw_line_step(&start, direction, d, &err);
	}
}

void	highlight_line_step(mlx_image_t *img, t_IntPair *start,
		t_IntPair direction, int *params)
{
	uint8_t		*pixelstart;
	uint32_t	current_color;
	int			e2;

	if (start->x >= 0 && start->x < (int)img->width && start->y >= 0
		&& start->y < (int)img->height)
	{
		pixelstart = &img->pixels[(start->y * img->width + start->x) * BPP];
		current_color = *(uint32_t *)pixelstart;
		ft_mlx_highlight_pixel(pixelstart, current_color);
	}
	e2 = 2 * params[0];
	if (e2 >= params[2])
	{
		params[0] += params[2];
		start->x += direction.x;
	}
	if (e2 <= params[1])
	{
		params[0] += params[1];
		start->y += direction.y;
	}
}

void	highlight_line_between_pixels(mlx_image_t *img, t_IntPair start,
		t_IntPair end)
{
	t_IntPair	direction;
	int			params[3];

	params[2] = -abs(end.y - start.y);
	params[1] = abs(end.x - start.x);
	if (start.y < end.y)
		direction.y = 1;
	else
		direction.y = -1;
	if (start.x < end.x)
		direction.x = 1;
	else
		direction.x = -1;
	params[0] = params[1] + params[2];
	while (start.x != end.x || start.y != end.y)
		highlight_line_step(img, &start, direction, params);
}
