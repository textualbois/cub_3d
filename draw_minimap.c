/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:53:08 by isemin            #+#    #+#             */
/*   Updated: 2025/02/02 19:42:09 by isemin           ###   ########.fr       */
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

void	color_mini_map(mlx_image_t *map_img, t_mini_map *map) //replace the
{
	int x;
	int y;
	int mHeight;
	int mWidth;

	x = 0;
	mHeight = 8; // todo
	mWidth = 8; // todo
	while (x < map->visible_size.x * map->ppu)
	{
		y = 0;
		while (y < map->visible_size.y * map->ppu)
		{
			if ((x + (int)map->view_port.x) % (WIDTH / mWidth) == 0 || (y + (int)map->view_port.y) % (HEIGHT / mHeight) <= 1)
				mlx_put_pixel(map_img, x, y, 0x003333FF); // if grid
			else
			{
				if (map->map[(int)(y / (HEIGHT / mHeight))][(int)(x / (WIDTH / mWidth))] == 1)
					mlx_put_pixel(map_img, x, y, 0xFF0000FF); // if wall
				else
					mlx_put_pixel(map_img, x, y, 0xFFFFAAFF); // if empty
			}
			y++;
		}
		x++;
	}
}
