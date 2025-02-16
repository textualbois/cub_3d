/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:53 by isemin            #+#    #+#             */
/*   Updated: 2025/02/16 02:42:10 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_World_Controller *init_world(t_config *config)
{
	t_World_Controller *world;

	world = (t_World_Controller *)malloc(sizeof(t_World_Controller));
	if (!world)
		return (NULL);
	world->size = (t_IntPair){config->map.height * TILE_SIZE, config->map.width * TILE_SIZE}; // change to map.size() * 10, map[0].size() * 10
	world->window = initialize_window();
	if (!world->window)
	{
		free(world);
		return (NULL);
	}
	world->player = init_mini_character((t_IntPair){config->player.pos.x, config->player.pos.y}, config->player); // actual poisiton will depend on input
	if (!world->player)
	{
		free(world);
		return (NULL);
	}
	world->mini_map = init_minimap(config);

	if (init_images(world) != 0)//, map) != 0)
	{
		printf("init images failedn\n");
		free(world->player);
		free(world->mini_map);
		free(world);
		return (NULL);
	}

	if (init_textures(world, config) != 0)
	{
		printf("init textures failed\n");
		free(world->player);
		free(world->mini_map);
		//destroy_images(world);
		free(world);
		return (NULL);
	}
		world->frameCounter = init_frame_counter(world->window);
	if (!world->frameCounter)
	{
		free(world->player);
		free(world);
	}
	return (world);
}

