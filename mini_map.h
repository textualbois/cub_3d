/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:59 by isemin            #+#    #+#             */
/*   Updated: 2025/02/02 19:34:37 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_MAP_H
# define MINI_MAP_H

#include "MLX42/MLX42.h"
#include "types_numeric.h"
#include "character.h"
#include "libft/libft.h"

typedef struct	s_mini_map{

	int				map[8][8];
	t_IntPair		size_int; // map grid dimensions
	t_DoublePair	size; // size of the world // map grid dimensions * TILE_SIZE
	t_DoublePair	view_port; // left and bottom-most corner of visible zone
	t_DoublePair	visible_size; // distance from view_port to right and top-most corner of visible zone
	int				ppu; // pixels per unit of size. for example we have 8 tiles,
						// each tile is 10 units of land, where each unit is 10 pixels
}	t_mini_map;


t_mini_map	*init_minimap(int map[8][8]);
void		centre_mini_map(t_mini_map *map, t_character *player);

#endif
