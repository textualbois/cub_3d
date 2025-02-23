/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:01 by isemin            #+#    #+#             */
/*   Updated: 2025/02/23 19:38:22 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "mini_map.h"
#include "parser/parser.h"

t_IntPair	calc_vis_size(int vis_tiles, int tile_size, int map_width,
		int map_height)
{
	int	size;

	size = vis_tiles * tile_size;
	if (size > map_width * tile_size || size > map_height * tile_size)
	{
		if (map_width < map_height)
			size = map_width * tile_size;
		else
			size = map_height * tile_size;
	}
	return ((t_IntPair){size, size});
}

t_mini_map	*allocate_minimap_struct(t_config *config)
{
	t_mini_map	*minimap;

	minimap = malloc(sizeof(t_mini_map));
	if (!minimap)
		return (NULL);
	minimap->map = malloc(sizeof(int *) * config->map.height);
	if (!minimap->map)
	{
		free(minimap);
		return (NULL);
	}
	return (minimap);
}

int	allocate_minimap_rows(t_mini_map *minimap, t_config *config)
{
	int	i;

	i = 0;
	while (i < config->map.height)
	{
		minimap->map[i] = malloc(sizeof(int) * config->map.width);
		if (!minimap->map[i])
		{
			while (--i >= 0)
			{
				free(minimap->map[i]);
			}
			free(minimap->map);
			free(minimap);
			return (1);
		}
		i++;
	}
	return (0);
}

t_mini_map	*allocate_minimap_memory(t_config *config)
{
	t_mini_map	*minimap;

	minimap = allocate_minimap_struct(config);
	if (!minimap)
		return (NULL);
	if (allocate_minimap_rows(minimap, config) != 0)
		return (NULL);
	return (minimap);
}

t_mini_map	*init_minimap(t_config *config)
{
	t_mini_map	*minimap;

	minimap = allocate_minimap_memory(config);
	if (!minimap)
		return (NULL);
	fill_minimap_tiles(minimap, config);
	minimap->size_int = (t_IntPair){config->map.width, config->map.height};
	minimap->size = (t_IntPair){minimap->size_int.x * TILE_SIZE,
		minimap->size_int.y * TILE_SIZE};
	minimap->visible_size = calc_vis_size(VISIBLE_TILES, TILE_SIZE,
			config->map.width, config->map.height);
	minimap->ppu = PPU / 5;
	return (minimap);
}
