/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:53:08 by isemin            #+#    #+#             */
/*   Updated: 2025/02/17 12:50:25 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

unsigned int	get_tile_color(char tile)
{
	if (tile == '1')
		return (0x880000FF);
	else if (tile == '0')
		return (0x888855FF);
	else if (tile == ' ')
		return (0x000000FF);
	else
		return (0x888888FF);
}

void	fill_mini_map_tile(mlx_image_t *map_img, t_mini_map *mini_map,
		t_IntPair pix)
{
	t_IntPair		cell;
	char			tile;
	unsigned int	color;

	cell.x = (pix.x / mini_map->ppu + mini_map->view_port.x) / TILE_SIZE;
	cell.y = (pix.y / mini_map->ppu + mini_map->view_port.y) / TILE_SIZE;
	if (cell.x >= mini_map->size_int.x)
		cell.x = mini_map->size_int.x - 1;
	if (cell.y >= mini_map->size_int.y)
		cell.y = mini_map->size_int.y - 1;
	tile = mini_map->map[cell.y][cell.x];
	color = get_tile_color(tile);
	mlx_put_pixel(map_img, pix.x, pix.y, color);
}

void	draw_mini_map_grid(mlx_image_t *map_img, t_mini_map *mini_map)
{
	t_IntPair	pix;

	pix.x = 0;
	while (pix.x < mini_map->visible_size.x * mini_map->ppu)
	{
		pix.y = 0;
		while (pix.y < mini_map->visible_size.y * mini_map->ppu)
		{
			if ((((pix.x / mini_map->ppu) + mini_map->view_port.x)
					% TILE_SIZE == 0) || ((pix.y / mini_map->ppu
						+ mini_map->view_port.y) % TILE_SIZE == 0))
				mlx_put_pixel(map_img, pix.x, pix.y, 0x000000FF);
			pix.y++;
		}
		pix.x++;
	}
}

void	color_mini_map(mlx_image_t *map_img, t_mini_map *mini_map)
{
	t_IntPair	pix;

	draw_mini_map_grid(map_img, mini_map);
	pix.x = 0;
	while (pix.x < mini_map->visible_size.x * mini_map->ppu)
	{
		pix.y = 0;
		while (pix.y < mini_map->visible_size.y * mini_map->ppu)
		{
			fill_mini_map_tile(map_img, mini_map, pix);
			pix.y++;
		}
		pix.x++;
	}
}
