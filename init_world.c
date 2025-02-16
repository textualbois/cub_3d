/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:53 by isemin            #+#    #+#             */
/*   Updated: 2025/02/15 17:02:51 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_World_Controller *init_world(t_config *config)
{
	t_World_Controller *world;

	world = (t_World_Controller *)malloc(sizeof(t_World_Controller));
	malloc_counter(1, MALLOC, "world init malloc\n");
	if (!world)
		return (NULL);
	world->size = (t_IntPair){config->map.height * TILE_SIZE, config->map.width * TILE_SIZE}; // change to map.size() * 10, map[0].size() * 10
	world->window = initialize_window();
	if (!world->window)
	{
		free(world);
		malloc_counter(-1, MALLOC, "world free\n");
		return (NULL);
	}
	world->player = init_mini_character((t_IntPair){config->player.pos.x, config->player.pos.y}, config->player); // actual poisiton will depend on input
	if (!world->player)
	{
		free(world);
		malloc_counter(-1, MALLOC, "world free\n");
		return (NULL);
	}
	world->mini_map = init_minimap(config);

	if (init_images(world) != 0)//, map) != 0)
	{
		printf("init images failedn\n");
		free(world->player);
		malloc_counter(-1, MALLOC, "world->player free\n");
		free(world->mini_map);
		malloc_counter(-1, MALLOC, "world->minimap free\n");
		free(world);
		malloc_counter(-1, MALLOC, "world free\n");
		return (NULL);
	}

	if (init_textures(world, config) != 0)
	{
		printf("init textures failed\n");
		free(world->player);
		malloc_counter(-1, MALLOC, "world-> free\n");
		free(world->mini_map);
		malloc_counter(-1, MALLOC, "world->minimap free\n");
		//free images?
		// free(world->texture_ea);
		// free(world->texture_no);
		// free(world->texture_so);
		// free(world->texture_we);
		free(world);
		malloc_counter(-1, MALLOC, "world free\n");
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

