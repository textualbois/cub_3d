/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:49:48 by isemin            #+#    #+#             */
/*   Updated: 2025/02/15 20:08:55 by isemin           ###   ########.fr       */
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

static void select_texture(t_renderData *data, t_World_Controller *world)
{
	if (data->txtr_code == NORTH)
		data->texture = world->texture_no;
	else if (data->txtr_code == EAST)
		data->texture = world->texture_ea;
	else if (data->txtr_code == SOUTH)
		data->texture = world->texture_so;
	else if (data->txtr_code == WEST)
		data->texture = world->texture_we;
}

void	draw_world(t_World_Controller *world)
{
	t_IntPair	miniCharImgPos;

	miniCharImgPos.x = (world->player->pos.x / world->size.x) * world->map_img->width - (world->miniCharacter->width / 2);
	miniCharImgPos.y = (world->player->pos.y / world->size.y) * world->map_img->height - (world->miniCharacter->height / 2);
	printf("char image positions x: %d, y: %d\n", miniCharImgPos.x, miniCharImgPos.y);
	fflush(stdout);
	mlx_image_to_window(world->window, world->world3d, 0, 0);
	mlx_image_to_window(world->window, world->map_img, world->window->width / 100, world->window->height - world->map_img->height - world->window->height / 100);
	// color_mini_map(world->map_img, world->map);
	mlx_image_to_window(world->window, world->miniCharacter, miniCharImgPos.x, miniCharImgPos.y);
	// ft_color_mini_character_direction(world->miniCharacter, 0xFF0000FF, world->player);



}


void	redraw(void *param)
{
	t_World_Controller *world;

	world = (t_World_Controller *)param;
	write(1, "redraw\n", 7);
	centre_mini_map(world->mini_map, world->player); // if player moves we first try to move the map view
	color_mini_map(world->map_img, world->mini_map);
	// player is drawn relative to his image, so we need to move the image
	centre_character_img(world, world->mini_map, world->player->pos); // then we move the player image box, if hes close to a border
	// sleep(3);
	raycasting(world); // then we draw the rays
	ft_color_mini_character(world->miniCharacter, 0x000000FF);
	// color_rays
	//ft_color_mini_character_direction(world->miniCharacter, 0xFF0000FF, world->player); // then we draw the player
	// color_sky
	// color_floor
	// color_wall
	// color_door
	// color_mini_character_direction
	write(1, "redraw_end\n", 11);
}

void	raycasting(t_World_Controller *world)
{
	printf("raycasting\n");
	t_renderData	data;
	int				x;
	double			radians_increment;

	radians_increment = - (FOV * PI / 180 )/ world->window->width;
	data.rayDir = normalise_radians(world->player->angle.x - radians_increment * (world->window->width / 2));
	x = 0;
	data.playerDir = world->player->angle;
	data.playerPos = world->player->pos;
	// printf("raycasting loop\n");
	// fflush(stdout);

	while (x < world->window->width)
	{

		ray_find_wall(world->mini_map, world->player, &data);
		select_texture(&data, world);
		// printf("raycasting loop %d out of %d hit x: %f, y: %f\n", x + 1, world->window->width, hit.x, hit.y);

		// fflush(stdout);
		drawray(world->player, world->map_img, world->mini_map, data.hit);
		draw3d(world->world3d, &data, x);
		//  distance(data.hit, data.playerPos),
		// 	normalise_radians(
		// 		data.playerdir.x - data.rayDir), data.plyerdir.y, x);
		data.rayDir = normalise_radians(data.rayDir + radians_increment);
		// printf("next loop\n");
		x++;
	}
}
