/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_mmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:39:44 by isemin            #+#    #+#             */
/*   Updated: 2025/02/12 23:44:35 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "draw.h"

static void	ft_mlx_highlight_pixel(uint8_t *pixel, uint32_t color)
{

	uint8_t alpha = (color >> 24) & 0xFF;
	uint8_t red = (color >> 16) & 0xFF;
	uint8_t green = (color >> 8) & 0xFF;
	uint8_t blue = color & 0xFF;

	uint8_t newRed = (uint8_t)fmin(255, red * 1.05);
	uint8_t newGreen = (uint8_t)fmin(255, green * 1.05);
	uint8_t newBlue = (uint8_t)fmin(255, blue * 1.05);

	uint32_t newColor = (alpha << 24) | (newRed << 16) | (newGreen << 8) | newBlue;

	*(uint32_t*)pixel = newColor;
}

void	drawray(t_character *player, mlx_image_t *map_img, t_mini_map *mini_map, t_DoublePair hit)
{
	t_IntPair	start;
	t_IntPair	end;

	if (hit.x < 0 || hit.y < 0)
		return ;
		// draw_line_between_pixels(map_img, start, end, 0xFFFFFFFF);

	start.x = (player->pos.x - mini_map->view_port.x) / mini_map->visible_size.x * map_img->width;
	start.y = (player->pos.y - mini_map->view_port.y) / mini_map->visible_size.y * map_img->height;
	end.x = (hit.x - mini_map->view_port.x) / mini_map->visible_size.x * map_img->width;
	end.y = (hit.y - mini_map->view_port.y) / mini_map->visible_size.y * map_img->height;
	// if (map_img == NULL)
		// printf("map_img is NULL\n");
	// if (end.x >= 0 && end.y >= 0)
	highlight_line_between_pixels(map_img, start, end);
	// draw_line_between_pixels(map_img, start, end, 0xFFFFFFFF);
	// printf("drew a line\n");
}


void draw_line_between_pixels(mlx_image_t *img, t_IntPair start, t_IntPair end, int color)
{
	t_IntPair	d;
	t_IntPair	direction;
	int			err;
	int			e2;
	// printf("image size is x: %d, y: %d\n", img->width, img->height);
	d.y = -abs(end.y - start.y);
	d.x = abs(end.x - start.x);
	direction.y = start.y < end.y ? 1 : -1;
	direction.x = start.x < end.x ? 1 : -1;
	err = d.x + d.y;
	while (start.x != end.x || start.y != end.y)
	{
		if (start.x >= 0 && start.x < (int)img->width && start.y >= 0 && start.y < (int)img->height)
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
	printf("drew a line\n");
}

void highlight_line_between_pixels(mlx_image_t *img, t_IntPair start, t_IntPair end)
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
		if (start.x >= 0 && start.x < (int)img->width && start.y >= 0 && start.y < (int)img->height)
		{
			uint8_t* pixelstart = &img->pixels[(start.y * img->width + start.x) * BPP];
			uint32_t currentColor = *(uint32_t*)pixelstart;
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
