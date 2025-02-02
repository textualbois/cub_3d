/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:23 by isemin            #+#    #+#             */
/*   Updated: 2025/02/01 21:34:46 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

int	init_images(t_World_Controller *world)//, int map[8][8])
{
	world->map_img = init_image_minimap(world->window);//, map);
	if (!world->map_img)
		return (1);
	world->miniCharacter = init_image_mini_character(world->window,
			world->player, (t_IntPair){9, 9});
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
	if (miniCharacter)
	{
		ft_color_mini_character_direction(miniCharacter, 0xFF0000FF, player);
	}
	return (miniCharacter);
}

mlx_image_t	*init_image_minimap(mlx_t *window)//, int map[8][8])
{
	mlx_image_t	*minimap;

	minimap = mlx_new_image(window, WIDTH, HEIGHT);
	if (!minimap)
		return (NULL);
	//color_mini
	return (minimap);
}
