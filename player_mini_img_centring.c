/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mini_img_centring.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 21:30:06 by isemin            #+#    #+#             */
/*   Updated: 2025/02/19 18:27:53 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void	centre_character_img(t_World_Controller *world, t_mini_map *map,
		t_DoublePair pos)
{
	if (map->view_port.y <= 0 || map->view_port.y >= map->size.y
		- map->visible_size.y)
		uncentre_character_img_v(world, map, pos);
	else
		centre_character_img_v(world);
	if (map->view_port.x <= 0 || map->view_port.x >= map->size.x
		- map->visible_size.x)
		uncentre_character_img_h(world, map, pos);
	else
		centre_character_img_h(world);
}

void	uncentre_character_img_v(t_World_Controller *world, t_mini_map *map,
		t_DoublePair pos)
{
	int	pixel_offset;

	if (pos.y < map->visible_size.y / 2)
	{
		pixel_offset = (int)(pos.y / map->visible_size.y
				* world->map_img->height);
		world->mini_character->instances[0].y = world->map_img->instances[0].y
			+ pixel_offset - world->mini_character->height / 2;
	}
	else if (pos.y > map->size.y - map->visible_size.y / 2)
	{
		pixel_offset = (int)((pos.y - map->view_port.y) / map->visible_size.y
				* world->map_img->height);
		world->mini_character->instances[0].y = world->map_img->instances[0].y
			+ pixel_offset - world->mini_character->height / 2;
	}
}

void	centre_character_img_v(t_World_Controller *world)
{
	world->mini_character->instances[0].y = world->map_img->instances[0].y
		+ world->map_img->height / 2 - world->mini_character->height / 2;
}

void	uncentre_character_img_h(t_World_Controller *world, t_mini_map *map,
		t_DoublePair pos)
{
	int	pixel_offset;

	if (pos.x < map->visible_size.x / 2)
	{
		pixel_offset = (int)(pos.x / map->visible_size.x
				* world->map_img->width);
		world->mini_character->instances[0].x = world->map_img->instances[0].x
			+ pixel_offset - world->mini_character->width / 2;
	}
	else if (pos.x > map->size.x - map->visible_size.x / 2)
	{
		pixel_offset = (int)((pos.x - map->view_port.x) / map->visible_size.x
				* world->map_img->width);
		world->mini_character->instances[0].x = world->map_img->instances[0].x
			+ pixel_offset - world->mini_character->width / 2;
	}
}

void	centre_character_img_h(t_World_Controller *world)
{
	world->mini_character->instances[0].x = world->map_img->instances[0].x
		+ world->map_img->width / 2 - world->mini_character->width / 2;
}
