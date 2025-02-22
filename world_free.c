/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:16:27 by isemin            #+#    #+#             */
/*   Updated: 2025/02/22 23:43:17 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

static void free_wolrd_images(t_World_Controller *world)
{
	if (world->map_img)
	{
		mlx_delete_image(world->window, world->map_img);
		world->map_img = NULL;
	}
	if (world->mini_character)
	{
		mlx_delete_image(world->window, world->mini_character);
		world->mini_character = NULL;
	}
}

static void free_world_player(t_World_Controller *world)
{
	malloc_counter(__FILE__, __func__, __LINE__,-1, MALLOC, "world->player free\n", world->player);
	free(world->player);
	world->player = NULL;
}

static void free_world_mini_map(t_World_Controller *world)
{
	int	i;

	i = 0;
	while (i < world->mini_map->size_int.y)
	{
		malloc_counter(__FILE__, __func__, __LINE__,-1, MALLOC, "world->mini_map->map[i] free\n", world->mini_map->map[i]);
		free(world->mini_map->map[i]);
		world->mini_map->map[i] = NULL;
		i++;
	}
	malloc_counter(__FILE__, __func__, __LINE__,-1, MALLOC, "world->mini_map->map free\n", world->mini_map->map);
	free(world->mini_map->map);
	world->mini_map->map = NULL;
	malloc_counter(__FILE__, __func__, __LINE__,-1, MALLOC, "world->mini_map free\n", world->mini_map);
	free(world->mini_map);
	world->mini_map = NULL;
}

void free_world_full(t_World_Controller *world)
{
	free_wolrd_images(world);
	free_world_player(world);
	free_world_mini_map(world);
	mlx_close_window(world->window);
	mlx_terminate(world->window);
	malloc_counter(__FILE__, __func__, __LINE__,-1, MALLOC, "world free\n", world);
	free(world);
	world = NULL;
}

