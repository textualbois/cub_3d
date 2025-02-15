/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:27 by isemin            #+#    #+#             */
/*   Updated: 2025/02/15 20:08:12 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "character.h"

t_character	*init_mini_character(t_IntPair size, t_character player)
{
	t_character	*mini_player;

	mini_player = (t_character *)malloc(sizeof(t_character));
	if (mini_player)
	{
		mini_player->size = size;
		mini_player->angle.x = player.angle.x;
		mini_player->angle.y = player.angle.y;
		mini_player->pos.x = player.pos.x * TILE_SIZE; // + TILE_SIZE / 2; ??
		mini_player->pos.y = player.pos.y * TILE_SIZE; // + TILE_SIZE / 2; ??
	}
	return (mini_player);
}
