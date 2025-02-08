/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:01 by isemin            #+#    #+#             */
/*   Updated: 2025/02/08 01:12:22 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "mini_map.h"
#include "parser/parser.h"

/* Преобразует символ карты в числовое значение для мини-карты.
   Например, если символ '1' означает стену, то возвращается 1, 
   а для остальных (например, '0', 'N', 'S', 'E', 'W', ' ') — 0.
   При необходимости настройте логику преобразования. */
static int	convert_tile(char c)
{
	if (c == '1')
		return (1);
	return (0);
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
	if (!minimap)
		return (NULL);

	/* Выделяем память для массива указателей на строки (количество строк = config.map.height) */
	minimap->map = malloc(sizeof(int *) * config->map.height);
	if (!minimap->map)
	{
		free(minimap);
		return (NULL);
	}

	/* Для каждой строки карты выделяем память и заполняем её значениями,
	   преобразованными функцией convert_tile() */
	i = 0;
	while (i < config->map.height)
	{
		minimap->map[i] = malloc(sizeof(int) * config->map.width);
		if (!minimap->map[i])
		{
			while (--i >= 0)
				free(minimap->map[i]);
			free(minimap->map);
			free(minimap);
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

	/* Настройка размеров мини-карты. Эти значения могут зависеть от логики приложения.
	   Здесь, например, фиксируется размер в тайлах и вычисляется размер в пикселях. */
	minimap->size_int = (t_IntPair){8, 8};  // Например, 8x8 тайлов (поменяйте при необходимости)
	minimap->size = (t_IntPair){minimap->size_int.x * TILE_SIZE,
	                            minimap->size_int.y * TILE_SIZE};
	minimap->visible_size = (t_IntPair){VISIBLE_TILES * TILE_SIZE,
	                                    VISIBLE_TILES * TILE_SIZE};
	minimap->ppu = PPU;
	return (minimap);
}
