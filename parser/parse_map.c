/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:18:22 by admin             #+#    #+#             */
/*   Updated: 2025/02/07 20:03:47 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_map_valid(t_map *map, t_config *config)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (!is_valid_map_char(map->grid[i][j]))
			{
				printf("Error: Map contains invalid characters.\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	if (!validate_map_structure(map, config))
		return (0);
	return (1);
}

static void	calculate_map_dimensions(t_map *map, char **lines)
{
	int	i;
	int	max_width;
	int	line_length;

	i = 0;
	max_width = 0;
	while (lines[i])
	{
		line_length = ft_strlen(lines[i]);
		if (line_length > max_width)
			max_width = line_length;
		i++;
	}
	map->height = i;
	map->width = max_width;
}

int	allocate_map_grid(t_config *config, char **lines)
{
	int		j;
	char	*padded;

	calculate_map_dimensions(&config->map, lines);
	config->map.grid = malloc(sizeof(char *) * (config->map.height + 1));
	malloc_counter(1, PARSER, "parsing map_grid malloc\n");
	if (!config->map.grid)
		return (0);
	j = 0;
	while (j < config->map.height)
	{
		padded = pad_line(lines[j], config->map.width);
		if (!padded)
		{
			free_lines(config->map.grid);
			return (0);
		}
		config->map.grid[j] = padded;
		j++;
	}
	config->map.grid[j] = NULL;
	return (1);
}

char	**parse_map(char **lines, t_config *config)
{
	int		skip;
	char	**map_lines;

	skip = skip_empty_lines(lines);
	map_lines = lines + skip;
	if (!allocate_map_grid(config, map_lines))
		return (NULL);
	if (!is_map_valid(&config->map, config))
		return (NULL);
	return (lines);
}
