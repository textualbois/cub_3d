/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:27 by isemin            #+#    #+#             */
/*   Updated: 2025/02/22 21:27:15 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "character.h"

t_character	*init_mini_character(t_IntPair size, t_character player)
{
	t_character	*mini_player;

	mini_player = (t_character *)malloc(sizeof(t_character));
	malloc_counter(__FILE__, __func__, __LINE__,1, MALLOC, "INIT_MINI_CHARACTER\n", mini_player);
	if (mini_player)
	{
		mini_player->size = size;
		mini_player->angle.x = player.angle.x;
		mini_player->angle.y = player.angle.y;
		mini_player->pos.x = player.pos.x * TILE_SIZE;
		mini_player->pos.y = player.pos.y * TILE_SIZE;
	}
	return (mini_player);
}
