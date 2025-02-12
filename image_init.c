/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:23 by isemin            #+#    #+#             */
/*   Updated: 2025/02/12 19:56:08 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "world.h"

#define SCALE_FACTOR 10

// int	init_images(t_World_Controller *world) //, int map[8][8])
// {
// 	t_IntPair	mini_player_img_size;

// 	mini_player_img_size.x = (world->mini_map->visible_size.x
// 			* world->mini_map->ppu) / (VISIBLE_TILES * SCALE_FACTOR);
// 	mini_player_img_size.y = (world->mini_map->visible_size.y
// 			* world->mini_map->ppu) / (VISIBLE_TILES * SCALE_FACTOR);
// 	printf("mini_player_img_size.x: %d\n", mini_player_img_size.x);
// 	printf("mini_player_img_size.y: %d\n", mini_player_img_size.y);
// 	fflush(stdout);
// 	world->map_img = init_image_minimap(world->window, world->mini_map);
// 		// return map variable for rescaling possibly
// 	if (!world->map_img)
// 		return (1);
// 	world->miniCharacter = init_image_mini_character(world->window,
// 			world->player, mini_player_img_size);
// 	if (!world->miniCharacter)
// 	{
// 		mlx_delete_image(world->window, world->map_img);
// 		// is this how you handle it?
// 		return (1);
// 	}
// 	return (0);
// }

int	init_images(t_World_Controller *world) //, int map[8][8])
{
	t_IntPair	mini_player_img_size;
	int mini_tile_size;

	mini_tile_size = TILE_SIZE * world->mini_map->ppu;
    if (mini_tile_size < 1)
        mini_tile_size = 1;
	// Пересчитываем так, чтобы умножение выполнялось до деления
	mini_player_img_size.x = mini_tile_size / 4;
    mini_player_img_size.y = mini_tile_size / 4;
	if (mini_player_img_size.x < 1)
        mini_player_img_size.x = 1;
    if (mini_player_img_size.y < 1)
        mini_player_img_size.y = 1;
	printf("mini_player_img_size.x: %d\n", mini_player_img_size.x);
	printf("mini_player_img_size.y: %d\n", mini_player_img_size.y);
	fflush(stdout);
	world->map_img = init_image_minimap(world->window, world->mini_map);
	if (!world->map_img)
		return (1);
	world->miniCharacter = init_image_mini_character(world->window,
			world->player, mini_player_img_size);
	if (!world->miniCharacter)
	{
		mlx_delete_image(world->window, world->map_img);
		return (1);
	}
	world->world3d = mlx_new_image(world->window, world->window->width, world->window->height);
	if (!world->world3d)
	{
		mlx_delete_image(world->window, world->map_img);
		mlx_delete_image(world->window, world->miniCharacter);
		return (1);
	}
	return (0);
}

mlx_image_t	*init_image_mini_character(mlx_t *window, t_character *player,
		t_IntPair size)
{
	mlx_image_t	*miniCharacter;

	miniCharacter = mlx_new_image(window, size.x, size.y);
	if (!miniCharacter)
	{
		printf("failed to create miniCharacter\n");
		fflush(stdout);
		return (NULL);
	}
	if (!player)
	{
		return (miniCharacter);
	}
	// if (miniCharacter)
	// {
	// void ft_color_mini_character(mlx_image_t *player, 0xFF0000FF);
	// ft_color_mini_character_direction(miniCharacter, 0xFF0000FF, player);
	// }
	printf("miniCharacter: %p\n", miniCharacter);
	fflush(stdout);
	return (miniCharacter);
}

mlx_image_t	*init_image_minimap(mlx_t *window, t_mini_map *map) //, int map[8][8])
{
	mlx_image_t	*map_img;
	int			ppu;

	ppu = map->ppu;
	map_img = mlx_new_image(window, map->visible_size.x * ppu,
			map->visible_size.y * ppu);
	// map_img = mlx_new_image(window, WIDTH, HEIGHT);
	if (!map_img)
		return (NULL);
	// color_mini
	return (map_img);
}
