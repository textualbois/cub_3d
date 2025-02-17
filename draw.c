/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:49:48 by isemin            #+#    #+#             */
/*   Updated: 2025/02/17 19:20:50 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

// static double normalise_radians(double angle)
// {
// 	while (angle < 0)
// 		angle += 2 * PI;
// 	while (angle >= 2 * PI)
// 		angle -= 2 * PI;
// 	return (angle);
// }

static void	select_texture(t_renderData *data, t_World_Controller *world)
{
	if (data->txtr_code == NORTH)
		data->texture = world->texture_no;
	else if (data->txtr_code == EAST)
		data->texture = world->texture_ea;
	else if (data->txtr_code == SOUTH)
		data->texture = world->texture_so;
	else if (data->txtr_code == WEST)
		data->texture = world->texture_we;
	data->t2t_ratio = (double)data->texture->width / TILE_SIZE;
	data->txtr.x *= data->t2t_ratio;
	data->txtr.y = 0;
}

void	draw_world(t_World_Controller *world)
{
	t_IntPair	miniCharImgPos;

	miniCharImgPos.x = (world->player->pos.x / world->size.x)
		* world->map_img->width - (world->miniCharacter->width / 2);
	miniCharImgPos.y = (world->player->pos.y / world->size.y)
		* world->map_img->height - (world->miniCharacter->height / 2);
	mlx_image_to_window(world->window, world->world3d, 0, 0);
	mlx_image_to_window(world->window, world->map_img, world->window->width
		/ 100, world->window->height - world->map_img->height
		- world->window->height / 100);
	mlx_image_to_window(world->window, world->miniCharacter, miniCharImgPos.x,
		miniCharImgPos.y);
}

void	redraw(void *param)
{
	t_World_Controller	*world;

	world = (t_World_Controller *)param;
	write(1, "redraw\n", 7);
	centre_mini_map(world->mini_map, world->player);
		// if player moves we first try to move the map view
	color_mini_map(world->map_img, world->mini_map);
	// player is drawn relative to his image, so we need to move the image
	centre_character_img(world, world->mini_map, world->player->pos);
		// then we move the player image box, if hes close to a border
	// sleep(3);
	raycasting(world); // then we draw the rays
	ft_color_mini_character(world->miniCharacter, 0x000000FF);
	write(1, "redraw_end\n", 11);
}

void	raycasting(t_World_Controller *world)
{
	t_renderData	data;
	int				x;
	double			radians_increment;

	printf("raycasting started\n");
	// Проверяем, что указатели не NULL
	if (!world)
	{
		printf("Error: world is NULL\n");
		return ;
	}
	if (!world->player)
	{
		printf("Error: world->player is NULL\n");
		return ;
	}
	if (!world->world3d)
	{
		printf("Error: world->world3d is NULL\n");
		return ;
	}
	if (!world->mini_map)
	{
		printf("Error: world->mini_map is NULL\n");
		return ;
	}
	radians_increment = -(FOV * PI / 180) / world->world3d->width;
	data.rayDir = normalise_radians(world->player->angle.x - radians_increment
			* (world->world3d->width / 2));
	x = 0;
	data.playerDir = world->player->angle;
	data.playerPos = world->player->pos;
	while (x < (int)world->world3d->width)
	{
		data.x = x;
		// Выводим отладочную информацию для текущего луча
		printf("Processing ray %d, rayDir: %f\n", x, data.rayDir);
		ray_find_wall(world->mini_map, world->player, &data);
		select_texture(&data, world);
		drawray(world->player, world->map_img, world->mini_map, data.hit);
		draw3d(world->world3d, &data, x);
		data.rayDir = normalise_radians(data.rayDir + radians_increment);
		x++;
	}
	printf("raycasting finished\n");
}
