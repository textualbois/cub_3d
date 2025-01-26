/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:27 by isemin            #+#    #+#             */
/*   Updated: 2025/01/26 18:55:24 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "character.h"

t_character* init_mini_character(t_IntPair size, t_IntPair pos)
{
	t_character *player;

	player = (t_character *)malloc(sizeof(t_character));
	if (player)
	{
		player->size = size;
		player->angle = PI / 2;
		player->pos.x = (double)pos.x;
		player->pos.y = (double)pos.y;
	}
	return (player);
}
