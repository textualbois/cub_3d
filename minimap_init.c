/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:01 by isemin            #+#    #+#             */
/*   Updated: 2025/02/05 23:54:54 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "mini_map.h"

t_mini_map	*init_minimap(int map[8][8])
{
	t_mini_map	*minimap;

	minimap = (t_mini_map *)malloc(sizeof(t_mini_map));
	if (!minimap)
		return (NULL);
	for (int i = 0; i < 8; i++)
	{
		ft_memcpy(minimap->map[i], map[i], 8 * sizeof(int));
	}
	minimap->size_int = (t_IntPair){8, 8}; //todo
	minimap->size = (t_IntPair){minimap->size_int.x * TILE_SIZE, minimap->size_int.y * TILE_SIZE};
	minimap->visible_size = (t_IntPair){VISIBLE_TILES * TILE_SIZE, VISIBLE_TILES * TILE_SIZE};
	minimap->ppu = PPU;
	return (minimap);
}

// redundant ??