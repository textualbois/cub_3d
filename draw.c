/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:49:48 by isemin            #+#    #+#             */
/*   Updated: 2025/02/01 18:04:20 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	draw_world(void *param)
{
	t_IntPair	miniCharImgPos;
	t_World_Controller *world;

	world = (t_World_Controller *)param;
	miniCharImgPos.x = (world->player->pos.x / world->size.x) * world->minimap->width - (world->miniCharacter->width / 2);
	miniCharImgPos.y = (world->player->pos.y / world->size.y) * world->minimap->height - (world->miniCharacter->height / 2);
	mlx_image_to_window(world->window, world->minimap, 0, 0);
	// color_mini_map(world->minimap, world->map);
	mlx_image_to_window(world->window, world->miniCharacter, miniCharImgPos.x, miniCharImgPos.y);
	ft_color_mini_character_direction(world->miniCharacter, 0xFF0000FF, world->player);


}


void	redraw(t_World_Controller *world)
{
	(void)world;
	// color_sky
	// color_floor
	// color_wall
	// color_door
	// color_minimap
	// color_mini_character
	// color_mini_character_direction
	// color_rays

}