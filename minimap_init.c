/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:01 by isemin            #+#    #+#             */
/*   Updated: 2025/02/02 09:27:53 by admin            ###   ########.fr       */
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
	minimap->size = (t_DoublePair){8 * TILE_SIZE, 8 * TILE_SIZE};
	minimap->visible_size = (t_DoublePair){VISIBLE_TILES * TILE_SIZE, VISIBLE_TILES * TILE_SIZE};
	return (minimap);
}

// redundant ??