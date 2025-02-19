/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:01 by isemin            #+#    #+#             */
/*   Updated: 2025/02/19 18:16:44 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "mini_map.h"
#include "parser/parser.h"

int	convert_tile(char c)
{
	return (c);
}

t_IntPair	calc_vis_size(int vis_tiles, int tile_size, int map_width,
		int mapHeight)
{
	int	size;

	size = vis_tiles * tile_size;
	if (size > map_width * tile_size || size > mapHeight * tile_size)
	{
		if (map_width < mapHeight)
			size = map_width * tile_size;
		else
			size = mapHeight * tile_size;
	}
	return ((t_IntPair){size, size});
}

t_mini_map	*allocate_minimap_struct(t_config *config)
{
	t_mini_map	*minimap;

	minimap = malloc(sizeof(t_mini_map));
	malloc_counter(1, MALLOC, "init minimap malloc\n");
	if (!minimap)
		return (NULL);
	minimap->map = malloc(sizeof(int *) * config->map.height);
	malloc_counter(1, MALLOC, "map rows malloc\n");
	if (!minimap->map)
	{
		free(minimap);
		malloc_counter(-1, MALLOC, "minimap free\n");
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
		malloc_counter(1, MALLOC, "map cell malloc\n");
		if (!minimap->map[i])
		{
			while (--i >= 0)
			{
				free(minimap->map[i]);
				malloc_counter(-1, MALLOC, "map cell free\n");
			}
			free(minimap->map);
			malloc_counter(-1, MALLOC, "map rows free\n");
			free(minimap);
			malloc_counter(-1, MALLOC, "minimap free\n");
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

void	fill_minimap_tiles(t_mini_map *minimap, t_config *config)
{
	int	i;
	int	j;

	i = 0;
	while (i < config->map.height)
	{
		j = 0;
		while (j < config->map.width)
		{
			minimap->map[i][j] = convert_tile(config->map.grid[i][j]);
			j++;
		}
		i++;
	}
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
