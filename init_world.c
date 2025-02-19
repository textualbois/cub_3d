/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:53 by isemin            #+#    #+#             */
/*   Updated: 2025/02/19 17:57:05 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_World_Controller	*allocate_world(t_config *config)
{
	t_World_Controller	*world;

	world = (t_World_Controller *)malloc(sizeof(t_World_Controller));
	malloc_counter(1, MALLOC, "world init malloc\n");
	if (!world)
		return (NULL);
	world->size = (t_IntPair){config->map.height * TILE_SIZE, config->map.width
		* TILE_SIZE};
	return (world);
}

int	init_world_components(t_World_Controller *world, t_config *config)
{
	world->window = initialize_window();
	if (!world->window)
	{
		free(world);
		malloc_counter(-1, MALLOC, "world free\n");
		return (1);
	}
	world->player = init_mini_character((t_IntPair){config->player.pos.x,
			config->player.pos.y}, config->player);
	if (!world->player)
	{
		free(world);
		malloc_counter(-1, MALLOC, "world free\n");
		return (1);
	}
	world->mini_map = init_minimap(config);
	return (0);
}

int	init_world_resources(t_World_Controller *world, t_config *config)
{
	if (init_images(world) != 0)
	{
		printf("init images failed\n");
		free(world->player);
		malloc_counter(-1, MALLOC, "world->player free\n");
		free(world->mini_map);
		malloc_counter(-1, MALLOC, "world->minimap free\n");
		free(world);
		malloc_counter(-1, MALLOC, "world free\n");
		return (1);
	}
	if (init_textures(world, config) != 0)
	{
		printf("init textures failed\n");
		free(world->player);
		malloc_counter(-1, MALLOC, "world->player free\n");
		free(world->mini_map);
		malloc_counter(-1, MALLOC, "world->minimap free\n");
		free(world);
		malloc_counter(-1, MALLOC, "world free\n");
		return (1);
	}
	return (0);
}

t_World_Controller	*init_world(t_config *config)
{
	t_World_Controller	*world;

	world = allocate_world(config);
	if (!world)
		return (NULL);
	if (init_world_components(world, config) != 0)
		return (NULL);
	if (init_world_resources(world, config) != 0)
		return (NULL);
	return (world);
}
