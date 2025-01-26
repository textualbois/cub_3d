/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:50 by isemin            #+#    #+#             */
/*   Updated: 2025/01/26 17:12:34 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t *init_minimap(mlx_t *window, int map[])
{
	mlx_image_t *minimap;
	int x = 0;
	int y = 0;
	int mHeight = 8;
	int mWidth = 8;
	// uint32_t color = 0;

	minimap = mlx_new_image(window, WIDTH, HEIGHT);
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (x % (WIDTH / mWidth) == 0 || y % (HEIGHT / mHeight) <= 1)
				mlx_put_pixel(minimap, x, y, 0x003333FF); // if grid
			else
			{
				if (map[(int)(y / (HEIGHT / mHeight)) * mWidth + (int)(x / (WIDTH / mWidth))] == 1)
					mlx_put_pixel(minimap, x, y, 0xFF0000FF); // if wall
				else
					mlx_put_pixel(minimap, x, y, 0xFFFFAAFF); // if empty
			}
			y++;
		}
		x++;
	}
	mlx_image_to_window(window, minimap, 0, 0);

	return (minimap);
}
