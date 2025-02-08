/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:59 by isemin            #+#    #+#             */
/*   Updated: 2025/02/08 01:08:16 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_MAP_H
# define MINI_MAP_H

#include "MLX42/MLX42.h"
#include "types_numeric.h"
#include "character.h"
#include "libft/libft.h"
#include "parser/parser.h"

typedef struct	s_mini_map{

	int				**map; // for what? i can put here [t_map->height] [t_map->width]
	t_IntPair		size_int; // map grid dimensions 
	t_IntPair	size; // size of the world // { size_int.x * TILE_SIZE, size_int.y * TILE_SIZE }
	t_IntPair	view_port; // left and bottom-most corner of visible zone
	t_IntPair	visible_size; // VISIBLE_TILES * TILE_SIZE
	int				ppu; // pixels per unit of size. for example we have 8 tiles,
						// each tile is 10 units of land, where each unit is 10 pixels
}	t_mini_map;


t_mini_map	*init_minimap(t_config *config);
void		centre_mini_map(t_mini_map *map, t_character *player);

#endif
