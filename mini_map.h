/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:59 by isemin            #+#    #+#             */
/*   Updated: 2025/02/01 21:08:11 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_MAP_H
# define MINI_MAP_H

#include "MLX42/MLX42.h"
#include "types_numeric.h"
#include "character.h"

typedef struct	s_mini_map{

	int				map[8][8];
	t_DoublePair	size;
	t_DoublePair	view_port;
	t_DoublePair	visible_size;
}	t_mini_map;


t_mini_map	*init_minimap(int map[8][8]);
void		centre_mini_map(t_mini_map *map, t_character *player);

#endif
