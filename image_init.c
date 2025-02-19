/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:23 by isemin            #+#    #+#             */
/*   Updated: 2025/02/19 17:49:00 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "world.h"

#define SCALE_FACTOR 10

int	init_minimap_images(t_World_Controller *world,
		t_IntPair mini_player_img_size)
{
	world->map_img = init_image_minimap(world->window, world->mini_map);
	if (!world->map_img)
		return (1);
	world->mini_character = init_image_mini_character(world->window,
			world->player, mini_player_img_size);
	if (!world->mini_character)
	{
		mlx_delete_image(world->window, world->map_img);
		return (1);
	}
	return (0);
}

int	init_images(t_World_Controller *world)
{
	t_IntPair	mini_player_img_size;
	int			mini_tile_size;

	mini_tile_size = TILE_SIZE * world->mini_map->ppu;
	if (mini_tile_size < 1)
		mini_tile_size = 1;
	mini_player_img_size.x = mini_tile_size / 4;
	mini_player_img_size.y = mini_tile_size / 4;
	if (mini_player_img_size.x < 1)
		mini_player_img_size.x = 1;
	if (mini_player_img_size.y < 1)
		mini_player_img_size.y = 1;
	if (init_minimap_images(world, mini_player_img_size))
		return (1);
	world->world3d = mlx_new_image(world->window, world->window->width,
			world->window->height);
	if (!world->world3d)
	{
		mlx_delete_image(world->window, world->map_img);
		mlx_delete_image(world->window, world->mini_character);
		return (1);
	}
	return (0);
}

mlx_image_t	*init_image_mini_character(mlx_t *window, t_character *player,
		t_IntPair size)
{
	mlx_image_t	*mini_character;

	mini_character = mlx_new_image(window, size.x, size.y);
	if (!mini_character)
	{
		printf("failed to create mini_character\n");
		fflush(stdout);
		return (NULL);
	}
	if (!player)
		return (mini_character);
	return (mini_character);
}

mlx_image_t	*init_image_minimap(mlx_t *window, t_mini_map *map)
{
	mlx_image_t	*map_img;
	int			ppu;

	ppu = map->ppu;
	map_img = mlx_new_image(window, map->visible_size.x * ppu,
			map->visible_size.y * ppu);
	if (!map_img)
		return (NULL);
	return (map_img);
}
