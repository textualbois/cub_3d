/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:27 by isemin            #+#    #+#             */
/*   Updated: 2025/02/09 11:13:20 by admin            ###   ########.fr       */
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
		mini_player->angle = player.angle;
		mini_player->pos.x = player.pos.x * TILE_SIZE;
		mini_player->pos.y = player.pos.y * TILE_SIZE;
	}
	return (mini_player);
}
