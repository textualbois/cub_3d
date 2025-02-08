/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mini_img_centring.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 21:30:06 by isemin            #+#    #+#             */
/*   Updated: 2025/02/08 20:05:42 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void	centre_character_img(t_World_Controller *world, t_mini_map *map, t_DoublePair pos)
{
	printf("map visible size x: %d, y: %d\n", map->visible_size.x, map->visible_size.y);
	printf("map size         x: %d, y: %d\n", map->size.x, map->size.y);
	printf("map view port    x: %d, y: %d\n", map->view_port.x, map->view_port.y);
	if (map->view_port.y <= 0 || map->view_port.y >= map->size.y - map->visible_size.y)
		uncentre_character_img_v(world, map, pos);
	else
		centre_character_img_v(world);
	if (map->view_port.x <= 0 || map->view_port.x >= map->size.x - map->visible_size.x)
		uncentre_character_img_h(world, map, pos);
	else
		centre_character_img_h(world);

	// sleep(1);

}

void uncentre_character_img_v(t_World_Controller *world, t_mini_map *map, t_DoublePair pos)
{
	int	pixel_offset;

	if (pos.y < map->visible_size.y / 2)
	{
		pixel_offset = (int)(pos.y / map->visible_size.y * world->map_img->height); //pixel = coord / bigcoord * bigpixel
		world->miniCharacter->instances[0].y = world->map_img->instances[0].y + pixel_offset - world->miniCharacter->height / 2; // need to factor in world->miniCharacter->height / 2
		printf("1 image position y: %d\n", world->miniCharacter->instances[0].y);
	}
	else if (pos.y > map->size.y - map->visible_size.y / 2)
	{
		pixel_offset = (int)((pos.y - map->view_port.y) / map->visible_size.y * world->map_img->height);
		world->miniCharacter->instances[0].y = world->map_img->instances[0].y + pixel_offset - world->miniCharacter->height / 2;
		printf("2 image position y: %d\n", world->miniCharacter->instances[0].y);
	}
	else
		printf("ELSE image position y: %d\n", world->miniCharacter->instances[0].y);
}

void	centre_character_img_v(t_World_Controller *world)
{
	printf("middle vertical centering\n");
	printf("pos.y: %f\n", world->player->pos.y);
	world->miniCharacter->instances[0].y = world->map_img->instances[0].y + world->map_img->height / 2 - world->miniCharacter->height / 2;
	printf("image position y: %d\n", world->miniCharacter->instances[0].y);
}

void uncentre_character_img_h(t_World_Controller *world, t_mini_map *map, t_DoublePair pos)
{
	int	pixel_offset;

	printf("pos.x: %f, vis_size %i, pos.x < map->visible_size.x / ƒ2 = %s\n", pos.x, map->visible_size.x, pos.x < map->visible_size.x / 2 ? "true" : "false");
	if (pos.x < map->visible_size.x / 2)
	{
		pixel_offset = (int)(pos.x / map->visible_size.x * world->map_img->width);
		world->miniCharacter->instances[0].x = world->map_img->instances[0].x + pixel_offset - world->miniCharacter->width / 2; // need to factor in world->miniCharacter->width / 2
		printf("1 image position x: %d\n", world->miniCharacter->instances[0].x);
	}
	else if (pos.x > map->size.x - map->visible_size.x / 2)
	{
		pixel_offset = (int)((pos.x - map->view_port.x) / map->visible_size.x * world->map_img->width);
		world->miniCharacter->instances[0].x = world->map_img->instances[0].x + pixel_offset - world->miniCharacter->width / 2;
		printf("2 image position x: %d\n", world->miniCharacter->instances[0].x);
	}
	else
		printf("ELSE image position x: %d\n", world->miniCharacter->instances[0].x);
}

void centre_character_img_h(t_World_Controller *world)
{
	printf("middle horizontal centering\n");
	printf("pos.x: %f\n", world->player->pos.x);
	world->miniCharacter->instances[0].x = world->map_img->instances[0].x + world->map_img->width / 2 - world->miniCharacter->width / 2;
	printf("image position x: %d\n", world->miniCharacter->instances[0].x);
}
