/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:27 by isemin            #+#    #+#             */
/*   Updated: 2025/02/08 17:14:10 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "character.h"

t_character* init_mini_character(t_IntPair size, t_DoublePair pos)
{
	t_character *player;

	player = (t_character *)malloc(sizeof(t_character));
	if (player)
	{
		player->size = size;
		player->angle = PI / 2;
		player->pos = pos;
	}
	return (player);
}
