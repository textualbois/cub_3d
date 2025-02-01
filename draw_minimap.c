/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:53:08 by isemin            #+#    #+#             */
/*   Updated: 2025/02/01 21:34:08 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	color_mini_map(mlx_image_t *map_img, t_mini_map *map)
{
	int x;
	int y;
	int mHeight;
	int mWidth;

	x = 0;
	y = 0;
	mHeight = 8; // todo
	mWidth = 8; // todo
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (x % (WIDTH / mWidth) == 0 || y % (HEIGHT / mHeight) <= 1)
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
