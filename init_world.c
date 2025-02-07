/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:53 by isemin            #+#    #+#             */
/*   Updated: 2025/02/08 00:35:10 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_World_Controller *init_world(t_map map)
{
	t_World_Controller *world;

	world = (t_World_Controller *)malloc(sizeof(t_World_Controller));
	if (!world)
		return (NULL);
	world->size = (t_IntPair){8 * TILE_SIZE, 8 * TILE_SIZE}; // change to map.size() * 10, map[0].size() * 10
	world->window = initialize_window();
	if (!world->window)
	{
		free(world);
		return (NULL);
	}
	world->player = init_mini_character((t_IntPair){5, 5}, (t_IntPair){world->size.x / 2, world->size.y / 2}); // actual poisiton will depend on input
	if (!world->player)
	{
		free(world);
		return (NULL);
	}
	world->map = init_minimap(map);

	// for (int i = 0; i < 8; i++)
	// {
	// 	ft_memcpy(world->map[i], map[i], 8 * sizeof(int));
	// }

	if (init_images(world) != 0)//, map) != 0)
	{
		printf("init images failedn\n");
		free(world->player);
		free(world->map);
		free(world);
		return (NULL);
	}


	// world->frameCounter = init_frame_counter();
	// if (!world->frameCounter)
	// {
	// 	free(world->player);
	// 	free(world);
	// 	return (NULL);
	// }
	return (world);
}

