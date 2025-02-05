/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mini_img_centring.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 21:30:06 by isemin            #+#    #+#             */
/*   Updated: 2025/02/02 23:14:17 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void	centre_character_img(t_World_Controller *world, t_mini_map *map, t_DoublePair pos)
{
	if (map->view_port.y <= 0)
		centre_character_img_v_low(world, map, pos);
	else if (map->view_port.y >= map->size.y - map->visible_size.y)
		centre_character_img_v_top(world, map, pos);
	else
		centre_character_img_v_middle(world);
	// if (map->view_port.x <= 0)
	// 	centre_character_img_h_left(world, map, pos);
	// else if (map->view_port.x >= map->size.x - map->visible_size.x)
	// 	centre_character_img_h_right(world, map, pos);
	// else
	// 	centre_character_img_h_middle(world, map, pos);

}

void	centre_character_img_v_low(t_World_Controller *world, t_mini_map *map, t_DoublePair pos)
{
	int	pixel_offset;
	printf("low vertical centering\n");
	printf("pos.y: %f\n", pos.y);

	if (pos.y < map->visible_size.y / 2)
	{
		pixel_offset = (int)(pos.y / map->visible_size.y * world->map_img->height);
		// world->miniCharacter->instances[0].y = world->map_img->height + pixel_offset; // need to factor in world->miniCharacter->height / 2
		world->miniCharacter->instances[0].y = world->map_img->instances[0].y + world->map_img->height - pixel_offset; // need to factor in world->miniCharacter->height / 2
	}
}

void	centre_character_img_v_top(t_World_Controller *world, t_mini_map *map, t_DoublePair pos)
{
	int	pixel_offset;
	printf("top vertical centering\n");
	printf("pos.y: %f\n", pos.y);

	if (pos.y > map->size.y - map->visible_size.y / 2)
	{
		pixel_offset = (int)((pos.y - map->view_port.y) / map->visible_size.y * world->map_img->height);
		world->miniCharacter->instances[0].y = world->map_img->instances[0].y + world->map_img->height - pixel_offset;
	}
}

void	centre_character_img_v_middle(t_World_Controller *world)
{
	printf("middle vertical centering\n");
	printf("pos.y: %f\n", world->player->pos.y);
	world->miniCharacter->instances[0].y = world->map_img->instances[0].y + world->map_img->height / 2;
}

// void	centre_character_img_h_left(t_World_Controller *world, t_mini_map *map, t_DoublePair pos)
// {

// }

// void	centre_character_img_h_right(t_World_Controller *world, t_mini_map *map, t_DoublePair pos)
// {

// }

// void	centre_character_img_h_middle(t_World_Controller *world, t_mini_map *map, t_DoublePair pos)
// {
// 	world->miniCharacter->instances[0].x = world->map_img->instances[0].x + world->map_img->width / 2;
// }
