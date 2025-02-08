/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:53:08 by isemin            #+#    #+#             */
/*   Updated: 2025/02/08 13:06:06 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

// we can speed up the drawing, by coloring the whole map with one color, then draw the walls, then draw the player
// this way we dont have to check if the pixel is a wall or not, we just draw the walls on top of the map
// also
// we can speed up the minimap draw, by drawing tiles as a whole, instead of pixel by pixel

// need to change the WIDTH / mwidth to be dynamic, depending on  .. ? WIDTH should be map->visible_size.x * map->ppu and
// mWidth should be VISIBLE_TILES
// on rescale of the screen we just change the PPU

// we also would need to take into account that the current ppu is ten, but when we scale the map down to the corner it would be different

void	color_mini_map(mlx_image_t *map_img, t_mini_map *mini_map)
{
	unsigned int	color;
	char			tile;

	int x, y;
	int mHeight, mWidth;
	int cellX, cellY;
	int tile_width, tile_height;
	mWidth = mini_map->size_int.x;
	mHeight = mini_map->size_int.y;
	tile_width = (mini_map->visible_size.x * mini_map->ppu) / mWidth;
	tile_height = (mini_map->visible_size.y * mini_map->ppu) / mHeight;
	x = 0;
	while (x < mini_map->visible_size.x * mini_map->ppu)
	{
		y = 0;
		while (y < mini_map->visible_size.y * mini_map->ppu)
		{
			/* Отрисовка линий сетки по границам тайлов */
			if (((x + (int)mini_map->view_port.x) % tile_width == 0) || ((y
						+ (int)mini_map->view_port.y) % tile_height <= 1))
			{
				mlx_put_pixel(map_img, x, y, 0x003333FF); // цвет линий сетки
			}
			else
			{
				/* Вычисляем, к какой ячейке принадлежит данный пиксель */
				cellX = x / tile_width;
				cellY = y / tile_height;
				/* На всякий случай,
					если вычисленные индексы равны mWidth/mHeight,
					принудительно уменьшаем их */
				if (cellX >= mWidth)
					cellX = mWidth - 1;
				if (cellY >= mHeight)
					cellY = mHeight - 1;
				tile = mini_map->map[cellY][cellX];
				if (tile == '1')
					color = 0xFF0000FF; // стена – красный
				else if (tile == '0')
					color = 0xFFFFAAFF; // пол – желтоватый
				else if (tile == ' ')
					color = 0x000000FF; // пустота – чёрный
				else
					color = 0xFFFFFFFF; // fallback – белый
				mlx_put_pixel(map_img, x, y, color);
			}
			y++;
		}
		x++;
	}
}
