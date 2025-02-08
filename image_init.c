/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:23 by isemin            #+#    #+#             */
/*   Updated: 2025/02/08 20:11:47 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "stdio.h"

int	init_images(t_World_Controller *world)//, int map[8][8])
{
	t_IntPair	mini_player_img_size;

	mini_player_img_size.x = (int)world->mini_map->visible_size.x / VISIBLE_TILES / 5 * world->mini_map->ppu; //change ten to ppu ??
	mini_player_img_size.y = (int)world->mini_map->visible_size.y / VISIBLE_TILES / 5 * world->mini_map->ppu; //
	printf("mini_player_img_size.x: %d\n", mini_player_img_size.x);
	printf("mini_player_img_size.y: %d\n", mini_player_img_size.y);
	fflush(stdout);
	world->map_img = init_image_minimap(world->window, world->mini_map);// return map variable for rescaling possibly
	if (!world->map_img)
		return (1);
	world->miniCharacter = init_image_mini_character(world->window,
			world->player, mini_player_img_size);
	if (!world->miniCharacter)
	{

		mlx_delete_image(world->window, world->map_img);
			// is this how you handle it?
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

mlx_image_t	*init_image_minimap(mlx_t *window, t_mini_map *map)//, int map[8][8])
{
	mlx_image_t	*map_img;
	int			ppu;

	ppu = map->ppu;
	map_img = mlx_new_image(window, map->visible_size.x * ppu, map->visible_size.y * ppu);
	//map_img = mlx_new_image(window, WIDTH, HEIGHT);
	if (!map_img)
		return (NULL);
	//color_mini
	return (map_img);
}
