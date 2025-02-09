/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:49:48 by isemin            #+#    #+#             */
/*   Updated: 2025/02/09 12:07:30 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	draw_world(t_World_Controller *world)
{
	t_IntPair	miniCharImgPos;

	miniCharImgPos.x = (world->player->pos.x / world->size.x) * world->map_img->width - (world->miniCharacter->width / 2);
	miniCharImgPos.y = (world->player->pos.y / world->size.y) * world->map_img->height - (world->miniCharacter->height / 2);
	printf("char image positions x: %d, y: %d\n", miniCharImgPos.x, miniCharImgPos.y);
	fflush(stdout);
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
	// raycasting(world); // then we draw the rays
	ft_color_mini_character(world->miniCharacter, 0xFF00FFFF);
	// color_rays
	//ft_color_mini_character_direction(world->miniCharacter, 0xFF0000FF, world->player); // then we draw the player
	// color_sky
	// color_floor
	// color_wall
	// color_door
	// color_mini_character_direction
	write(1, "redraw_end\n", 11);
}

// void	raycasting(t_World_Controller *world)
// {
// 	printf("raycasting\n");
// 	double		rayDir;
// 	t_DoublePair	hit;
// 	int			x;
// 	double		fov_radians;

// 	fov_radians = FOV * PI / 180;
// 	rayDir = world->player->angle - fov_radians / 2;
// 	x = 0;
// 	// printf("raycasting loop\n");
// 	// fflush(stdout);
// 	while (x < world->window->width)
// 	{
// 		hit = ray_find_wall(world->mini_map, world->player, rayDir);
// 		// printf("raycasting loop %d out of %d hit x: %f, y: %f\n", x + 1, world->window->width, hit.x, hit.y);

// 		// fflush(stdout);
// 		drawray(world->player, world->map_img, world->mini_map, hit);
// 		rayDir += fov_radians / world->window->width;
// 		if (rayDir < 0)
// 			rayDir += 2 * PI;
// 		else if (rayDir >= 2 * PI)
// 			rayDir -= 2 * PI;
// 		x++;
// 		// printf("next loop\n");
// 	}
// }
