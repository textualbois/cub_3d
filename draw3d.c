/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:32:15 by isemin            #+#    #+#             */
/*   Updated: 2025/02/15 18:30:55 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

// uint32_t	get_pixel_color(mlx_texture_t *texture, uint32_t tex_x,
// 		uint32_t tex_y)
// {
// 	uint8_t		*pixel;
// 	uint32_t	a;

// 	pixel = &texture->pixels[(texture->width * tex_y + tex_x) * 4];
// 	a = pixel[3];
// 	if (a == 0)
// 		return (0x00000000);
// 	return ((pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3]);
// }

static void draw_texture_line(mlx_image_t *img, int row_ind, int start, int end, int x, int color) {
	// if (end > (int)img->height)
	// 	end = img->height;
	//double ratio;

	(void)start;
	//ratio = end - start / texture_hieght;
	while (row_ind < end && row_ind < (int)img->height)
	{
		mlx_put_pixel(img, x, row_ind, color);
		row_ind++;
	}
	// {
	// 	mlx_put_pixel(img, x, start, color);
	// 	start++;
	// }
}
// 	t_wall_data		wall;
// 	uint32_t		tex_x;

// 	wall = calculate_wall_dimensions(data, distance_to_wall);
// 	wall.texture = get_wall_texture(data, ray);
// 	wall.step = (double)wall.texture->height / wall.height;
// 	if (wall.height > HEIGHT)
// 		wall.tex_pos = ((wall.height - HEIGHT) / 2) * wall.step;
// 	else
// 		wall.tex_pos = 0;
// 	tex_x = calculate_tex_x(ray->color, &wall, ray, data);
// 	draw_wall_slice(data, wall, tex_x, x);
// 	floor_drawing(data, wall, x);
// 	ceiling_drawing(data, wall, x);
// }

static void	draw_vertical_line(mlx_image_t *img, int start, int end, int x)
{
	int	i;
	int	color;

	i = 0;
	color = 0xFFF000FF;
	if (start > (int)img->height)
		start = img->height;
	// if (end > (int)img->height)
	// {
	// 	end = img->height;
	// }

	while (i < start)
	{
		mlx_put_pixel(img, x, i, 0xFF7220FF);
		i++;
	}

	printf("start: %d, end: %d\n", start, end);
	fflush(stdout);
	draw_texture_line(img, i, start, end, x, color);
	i = end;


	while (i < (int)img->height)
	{
		mlx_put_pixel(img, x, i, 0xFF0220FF);
		i++;
	}
		// mlx_put_pixel(img, x, start, 0xFFFFFFFF);
		// mlx_put_pixel(img, x, end - 1, 0xFFFFFFFF);
}

void	draw3d(mlx_image_t *world3d, double distance, double rad_delta, double pitch, int x)
{
	// t_IntPair window_size;
	// (void)rad_delta;
	distance *= cos(rad_delta);
	double lineH = TILE_SIZE * world3d->height / distance;
	double vertical_offset = (world3d->height / 2) * sin(pitch);
	int top = (world3d->height - lineH) / 2 + vertical_offset;
	int bottom = (world3d->height + lineH) / 2 + vertical_offset;
	// int mid = world3d->height / 2;
	draw_vertical_line(world3d, top, bottom, x);
}
