/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:25:36 by admin             #+#    #+#             */
/*   Updated: 2025/02/08 00:07:55 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_map_enclosed(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == '0' && !is_valid_cell(map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	has_invalid_spaces(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == ' ' && !is_sur_by_wals(map, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	count_players(t_map *map, t_config *config)
{
	int	i;
	size_t	j;
	int	count;

	count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < ft_strlen(map->grid[i]))
		{
			if (ft_strchr("NSEW", map->grid[i][j]))
			{
				count++;
				if (count == 1)
				{
					set_player_position(config, j, i, map->grid[i][j]);
					map->grid[i][j] = '0';
				}
			}
			j++;
		}
		i++;
	}
	return (count);
}

int	is_player_surrounded(t_config *config)
{
	int		row;
	int		col;
	char	neighbors[4];
	int		i;

	row = (int)config->player.pos.y;
	col = (int)config->player.pos.x;
	if (row <= 0 || row >= config->map.height - 1 || col <= 0
		|| col >= config->map.width - 1)
		return (0);
	neighbors[0] = config->map.grid[row - 1][col];
	neighbors[1] = config->map.grid[row + 1][col];
	neighbors[2] = config->map.grid[row][col - 1];
	neighbors[3] = config->map.grid[row][col + 1];
	i = 0;
	while (i < 4)
	{
		if (neighbors[i] != '0' && neighbors[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	validate_map_structure(t_map *map, t_config *config)
{
	if (!is_map_enclosed(map))
	{
		printf("Error: Map is not enclosed by walls.\n");
		return (0);
	}
	if (has_invalid_spaces(map))
	{
		printf("Error: Map contains invalid spaces.\n");
		return (0);
	}
	if (count_players(map, config) != 1)
	{
		printf("Error: Map must contain exactly one player.\n");
		return (0);
	}
	if (!is_player_surrounded(config))
	{
		printf("Error: Player cannot be on the edge of the map.\n");
		return (0);
	}
	return (1);
}
