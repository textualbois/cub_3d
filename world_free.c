/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:16:27 by isemin            #+#    #+#             */
/*   Updated: 2025/02/23 19:27:54 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

static void	free_world_textures(t_World_Controller *world)
{
	mlx_delete_texture(world->texture_no);
	mlx_delete_texture(world->texture_so);
	mlx_delete_texture(world->texture_we);
	mlx_delete_texture(world->texture_ea);
}

void	free_wolrd_images(t_World_Controller *world)
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

static void	free_world_player(t_World_Controller *world)
{
	free(world->player);
	world->player = NULL;
}

void	free_world_mini_map(t_World_Controller *world)
{
	int	i;

	i = 0;
	while (i < world->mini_map->size_int.y)
	{
		free(world->mini_map->map[i]);
		world->mini_map->map[i] = NULL;
		i++;
	}
	free(world->mini_map->map);
	world->mini_map->map = NULL;
	free(world->mini_map);
	world->mini_map = NULL;
}

void	free_world_full(t_World_Controller *world, int terminate_mlx)
{
	free_wolrd_images(world);
	free_world_textures(world);
	free_world_player(world);
	free_world_mini_map(world);
	mlx_close_window(world->window);
	if (terminate_mlx)
		mlx_terminate(world->window);
	free(world);
	world = NULL;
}
