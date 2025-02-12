/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:53:08 by isemin            #+#    #+#             */
/*   Updated: 2025/02/12 23:23:25 by isemin           ###   ########.fr       */
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

// instead of drawing the map pixel by pixel, we can draw the tiles as a whole, this would speed up the drawing

void	color_mini_map(mlx_image_t *map_img, t_mini_map *mini_map)
{
	unsigned int	color;
	char			tile;
	t_IntPair		pix;
	t_IntPair		cell;

	pix.x = 0;
	while (pix.x < mini_map->visible_size.x * mini_map->ppu) // pixels
	{
		pix.y = 0;
		while (pix.y < mini_map->visible_size.y * mini_map->ppu)
		{
			/* Отрисовка линий сетки по границам тайлов */
			if ((((pix.x / mini_map->ppu) + mini_map->view_port.x) % TILE_SIZE == 0) || ((pix.y / mini_map->ppu
						+ mini_map->view_port.y) % TILE_SIZE == 0))
			{
				mlx_put_pixel(map_img, pix.x, pix.y, 0x000000FF); // цвет линий сетки
			}
			else
			{
				/* Вычисляем, к какой ячейке принадлежит данный пиксель */
				cell.x = (pix.x / mini_map->ppu + mini_map->view_port.x) / TILE_SIZE;
				cell.y = (pix.y / mini_map->ppu + mini_map->view_port.y) / TILE_SIZE;
				// printf("cellX = %i, cellY = %i\n", cellX, cellY);
				/* На всякий случай,
					если вычисленные индексы равны mWidth/mHeight,
					принудительно уменьшаем их */ /// instead of this check we can substract 1 from cellX and CellY
				if (cell.x >= mini_map->size_int.x)
					cell.x = mini_map->size_int.x - 1;
				if (cell.y >= mini_map->size_int.y)
					cell.y =  mini_map->size_int.y - 1;
				tile = mini_map->map[cell.y][cell.x];
				if (tile == '1')
					color = 0x880000FF; // стена – красный
				else if (tile == '0')
					color = 0x888855FF; // пол – желтоватый
				else if (tile == ' ')
					color = 0x000000FF; // пустота – чёрный
				else
					color = 0x888888FF; // fallback – белый
				mlx_put_pixel(map_img, pix.x, pix.y, color);
			}
			pix.y++;
		}
		pix.x++;
	}
}
