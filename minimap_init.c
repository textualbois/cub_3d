/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:01 by isemin            #+#    #+#             */
/*   Updated: 2025/02/12 20:05:36 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "mini_map.h"
#include "parser/parser.h"

void	print_minimap_map(t_mini_map *minimap, t_config *config)
{
	int	i;
	int	j;

	i = 0;
	if (!minimap || !minimap->map)
		return ;
	while (i < config->map.height)
	{
		j = 0;
		while (j < config->map.width)
		{
			printf("%c", (char)minimap->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

/* Преобразует символ карты в числовое значение для мини-карты.
   Например, если символ '1' означает стену, то возвращается 1,
   а для остальных (например, '0', 'N', 'S', 'E', 'W', ' ') — 0.
   При необходимости настройте логику преобразования. */
int	convert_tile(char c)
{
	// if (c == '1')
	// 	return ('1');
	// if (c == ' ')
	// 	return (' ');
	// return ('0');
	return (c);
}

t_IntPair	calculateVisibleSize(int visibleTiles, int tileSize, int mapWidth,
		int mapHeight)
{
	int	size;

	size = visibleTiles * tileSize;
	if (size > mapWidth * tileSize || size > mapHeight * tileSize)
	{
		if (mapWidth < mapHeight)
		{
			size = mapWidth * tileSize;
		}
		else
		{
			size = mapHeight * tileSize;
		}
	}
	return ((t_IntPair){size, size});
}
/* Инициализирует структуру мини-карты на основе данных карты из config.
   Выделяется память для структуры и для двумерного массива целых чисел,
   в который копируются значения из config.map.grid с преобразованием символов. */
t_mini_map	*init_minimap(t_config *config)
{
	t_mini_map	*minimap;
	int			i;
	int			j;

	minimap = malloc(sizeof(t_mini_map));
	malloc_counter(1, MALLOC, "init minimap malloc\n");
	if (!minimap)
		return (NULL);
	/* Выделяем память для массива указателей на строки (количество строк = config.map.height) */
	minimap->map = malloc(sizeof(int *) * config->map.height);
	malloc_counter(1, MALLOC, "map rows malloc\n");
	if (!minimap->map)
	{
		free(minimap);
		malloc_counter(-1, MALLOC, "minimap free\n");
		return (NULL);
	}
	/* Для каждой строки карты выделяем память и заполняем её значениями,
		преобразованными функцией convert_tile() */
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
			malloc_counter(-1, MALLOC, "map free\n");
			return (NULL);
		}
		j = 0;
		while (j < config->map.width)
		{
			minimap->map[i][j] = convert_tile(config->map.grid[i][j]);
			j++;
		}
		i++;
	}
	print_minimap_map(minimap, config);
	/* Настройка размеров мини-карты. Эти значения могут зависеть от логики приложения.
		Здесь, например,
			фиксируется размер в тайлах и вычисляется размер в пикселях. */
	minimap->size_int = (t_IntPair){config->map.width, config->map.height};
		// Например, 8x8 тайлов (поменяйте при необходимости)
	minimap->size = (t_IntPair){minimap->size_int.x * TILE_SIZE, minimap->size_int.y * TILE_SIZE};
	minimap->visible_size = calculateVisibleSize(VISIBLE_TILES, TILE_SIZE,
			config->map.width, config->map.height) ;
	minimap->ppu = PPU /5 ;
	return (minimap);
}
