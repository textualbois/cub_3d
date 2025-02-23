/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:37:45 by vmamoten          #+#    #+#             */
/*   Updated: 2025/02/23 19:39:16 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_map.h"

int	convert_tile(char c)
{
	return (c);
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
