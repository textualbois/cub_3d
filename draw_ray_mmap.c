/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_mmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:39:44 by isemin            #+#    #+#             */
/*   Updated: 2025/02/09 18:54:06 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "draw.h"

void	drawray(t_character *player, mlx_image_t *map_img, t_mini_map *mini_map, t_DoublePair hit)
{
	t_IntPair	start;
	t_IntPair	end;

	start.x = (player->pos.x - mini_map->view_port.x) / mini_map->visible_size.x * map_img->width;
	start.y = (player->pos.y - mini_map->view_port.y) / mini_map->visible_size.y * map_img->height;
	end.x = (hit.x - mini_map->view_port.x) / mini_map->visible_size.x * map_img->width;
	end.y = (hit.y - mini_map->view_port.y) / mini_map->visible_size.y * map_img->height;
	// if (map_img == NULL)
		// printf("map_img is NULL\n");
	draw_line_between_pixels(map_img, start, end, 0xFF000000);
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
		if (start.x < 0 || start.x + 1 >= (int)img->width || start.y < 0 || start.y + 1 > (int)img->height)
		{
			printf("pixel is out of bounds x: %d, y: %d\n", start.x, start.y);
			break;
		}
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
