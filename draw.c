/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:49:48 by isemin            #+#    #+#             */
/*   Updated: 2025/02/02 23:07:15 by isemin           ###   ########.fr       */
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
	mlx_image_to_window(world->window, world->map_img, 0, 0);
	// color_mini_map(world->map_img, world->map);
	mlx_image_to_window(world->window, world->miniCharacter, miniCharImgPos.x, miniCharImgPos.y);
	// ft_color_mini_character_direction(world->miniCharacter, 0xFF0000FF, world->player);


}


void	redraw(void *param)
{
	t_World_Controller *world;

	world = (t_World_Controller *)param;
	write(1, "redraw\n", 7);
	centre_mini_map(world->map, world->player); // if player moves we first try to move the map view
	color_mini_map(world->map_img, world->map);
	// player is drawn relative to his image, so we need to move the image
	centre_character_img(world, world->map, world->player->pos); // then we move the player image box, if hes close to a border
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