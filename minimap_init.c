/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:01 by isemin            #+#    #+#             */
/*   Updated: 2025/01/27 20:08:44 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "mini_map.h"
#include "types_numeric.h"

mlx_image_t	*init_minimap(mlx_t *window, int map[])
{
	mlx_image_t	*minimap;
	int			mWidth;
	int			mHeight;
	int			mx;
	int			my;

	int x, y;
	mWidth = 8;
	mHeight = 8;
	minimap = mlx_new_image(window, WIDTH, HEIGHT);
	if (!minimap)
		return (NULL);
	for (x = 0; x < WIDTH; x++)
	{
		for (y = 0; y < HEIGHT; y++)
		{
			if (x % (WIDTH / mWidth) == 0 || y % (HEIGHT / mHeight) <= 1)
				mlx_put_pixel(minimap, x, y, 0x003333FF);
			else
			{
				mx = x / (WIDTH / mWidth);
				my = y / (HEIGHT / mHeight);
				if (map[my * mWidth + mx] == 1)
					mlx_put_pixel(minimap, x, y, 0xFF0000FF);// wall
				else
					mlx_put_pixel(minimap, x, y, 0xFFFFAAFF); // floor
			}
		}
	}
	return (minimap);
}

// redundant ??