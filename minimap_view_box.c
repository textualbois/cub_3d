/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_view_box.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:55:33 by isemin            #+#    #+#             */
/*   Updated: 2025/02/06 00:24:12 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_map.h"

void	centre_mini_map(t_mini_map *map, t_character *player)
{
	if (player->pos.x + map->visible_size.x / 2 > map->size.x)
		map->view_port.x = map->size.x - map->visible_size.x;
	else if (player->pos.x - map->visible_size.x / 2 < 0)
		map->view_port.x = 0;
	else
		map->view_port.x = player->pos.x - map->visible_size.x / 2;
	if (player->pos.y + map->visible_size.y / 2 > map->size.y)  // south border
		map->view_port.y = map->size.y - map->visible_size.y;
	else if (player->pos.y < map->visible_size.y / 2 ) // north border
		map->view_port.y = 0;
	else
		map->view_port.y = player->pos.y - map->visible_size.y / 2;
}

// void	centre_mini_map(t_mini_map *map, t_character *player)
// {
// 	if (player->pos.x + map->visible_size.x / 2 > map->size.x)
// 		map->view_port.x = map->size.x - map->visible_size.x;
// 	else if (player->pos.x - map->visible_size.x / 2 < 0)
// 		map->view_port.x = 0;
// 	else
// 		map->view_port.x = player->pos.x - map->visible_size.x / 2;
// 	if (player->pos.y + map->visible_size.y / 2 > map->size.y)
// 		map->view_port.y = map->size.y - map->visible_size.y;
// 	else if (player->pos.y - map->visible_size.y / 2 < 0)
// 		map->view_port.y = 0;
// 	else
// 		map->view_port.y = player->pos.y - map->visible_size.y / 2;
// }