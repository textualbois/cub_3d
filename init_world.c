/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:53 by isemin            #+#    #+#             */
/*   Updated: 2025/02/23 18:29:18 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void	copy_colors(int dest[3], int src[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		dest[i] = src[i];
		i++;
	}
}

t_World_Controller	*allocate_world(t_config *config)
{
	t_World_Controller	*world;

	world = (t_World_Controller *)malloc(sizeof(t_World_Controller));
	malloc_counter(__FILE__, __func__, __LINE__,1, MALLOC, "world init malloc\n", world);
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
		malloc_counter(__FILE__, __func__, __LINE__,-1, MALLOC, "world free\n", world);
		free(world);
		return (1);
	}
	world->player = init_mini_character((t_IntPair){config->player.pos.x,
			config->player.pos.y}, config->player);
	if (!world->player)
	{
		malloc_counter(__FILE__, __func__, __LINE__,-1, MALLOC, "world free\n", world);
		free(world);
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
		malloc_counter(__FILE__, __func__, __LINE__,-1, MALLOC, "world->player free\n", world->player);
		free(world->player);
		malloc_counter(__FILE__, __func__, __LINE__,-1, MALLOC, "world->minimap free\n", world->mini_map);
		free(world->mini_map);
		malloc_counter(__FILE__, __func__, __LINE__,-1, MALLOC, "world free\n", world);
		free(world);
		return (1);
	}
	if (init_textures(world, config) != 0)
	{
		free_wolrd_images(world);
		printf("init textures failed\n");
		malloc_counter(__FILE__, __func__, __LINE__,-1, MALLOC, "world->player free\n", world->player);
		free(world->player);
		malloc_counter(__FILE__, __func__, __LINE__,-1, MALLOC, "world->minimap free\n", world->mini_map);
		free(world->mini_map);
		malloc_counter(__FILE__, __func__, __LINE__,-1, MALLOC, "world free\n", world);
		free(world);
		return (1);
	}
	return (0);
}

t_World_Controller	*init_world(t_config *config)
{
	t_World_Controller	*world;

	world = allocate_world(config);
	if (!world)
		return (free_free_config(config), NULL);
	if (init_world_components(world, config) != 0)
		return (free_free_config(config), NULL);
	if (init_world_resources(world, config) != 0)
		return (free_free_config(config), NULL);
	copy_colors(world->ceiling_color, (config)->ceiling_color);
	copy_colors(world->floor_color, (config)->floor_color);
	free_free_config(config);
	return (world);
}
