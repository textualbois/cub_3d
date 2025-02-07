/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:26:10 by vmamoten          #+#    #+#             */
/*   Updated: 2025/02/07 16:53:49 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_map(char **map_grid, int map_width, int map_height)
{
	int	i;

	i = 0;
	printf("Map (%d x %d):\n", map_width, map_height);
	while (i < map_height)
	{
		printf("%s\n", map_grid[i]);
		i++;
	}
}

int	has_cub_extension(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	if (len > 4 && filename[len - 5] == '.')
		return (0);
	return (1);
}

int	is_valid_cell(t_map *map, int i, int j)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = ' ';
	down = ' ';
	left = ' ';
	right = ' ';
	if (i > 0)
		up = map->grid[i - 1][j];
	if (i < map->height - 1)
		down = map->grid[i + 1][j];
	if (j > 0)
		left = map->grid[i][j - 1];
	if (j < map->width - 1)
		right = map->grid[i][j + 1];
	if (i == 0 || i == map->height - 1 || j == 0 || j == map->width - 1)
		return (0);
	if (up == ' ' || down == ' ' || left == ' ' || right == ' ')
		return (0);
	return (1);
}

int	is_sur_by_wals(t_map *map, int i, int j)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = '1';
	down = '1';
	left = '1';
	right = '1';
	if (i > 0)
		up = map->grid[i - 1][j];
	if (i < map->height - 1)
		down = map->grid[i + 1][j];
	if (j > 0)
		left = map->grid[i][j - 1];
	if (j < map->width - 1)
		right = map->grid[i][j + 1];
	if ((up != '1' && up != ' ') || (down != '1' && down != ' '))
		return (0);
	if ((left != '1' && left != ' ') || (right != '1' && right != ' '))
		return (0);
	return (1);
}

int	is_valid_map_char(char c)
{
	if (c == ' ' || c == '1' || c == '0' || c == 'N' || c == 'E' || c == 'W'
		|| c == 'S')
		return (1);
	return (0);
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

double	get_angle_from_char(char dir)
{
	if (dir == 'N')
		return (3 * M_PI_2);
	if (dir == 'S')
		return (M_PI_2);
	if (dir == 'E')
		return (0);
	if (dir == 'W')
		return (M_PI);
	return (0);
}

void	set_player_position(t_config *config, int x, int y, char dir)
{
	config->player.pos.x = (double)x + 0.5;
	config->player.pos.y = (double)y + 0.5;
	config->player.angle = get_angle_from_char(dir);
}

int	count_players(t_map *map, t_config *config)
{
	int	i;
	int	j;
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

/*
 ************************ optimized ************************
 */

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

int	allocate_map_grid(t_config *config, char **lines)
{
	int		j;
	int		line_length;
	int		max_width;
	char	*padded;

	config->map.height = 0;
	while (lines[config->map.height])
		config->map.height++;
	config->map.grid = (char **)malloc(sizeof(char *) * (config->map.height
				+ 1));
	if (!config->map.grid)
		return (0);
	max_width = 0;
	j = 0;
	while (j < config->map.height)
	{
		line_length = ft_strlen(lines[j]);
		if (line_length > max_width)
			max_width = line_length;
		j++;
	}
	config->map.width = max_width;
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
	// print_map(lines, config->map.width, config->map.height);
	return (lines);
}

int	parse_texture(char *trimmed, char **texture)
{
	char	*value;

	value = ft_strtrim(trimmed + 2, " \t");
	if (!value)
		return (0);
	if (*texture)
		free(*texture);
	*texture = value;
	return (1);
}

// int	check_all_settings_present(t_config *config)
// {
// 	return (config->has_no && config->has_so && config->has_we &&
// 			config->has_ea && config->has_floor && config->has_ceiling);
// }

int	check_all_settings_present(t_config *config)
{
	if (!config->has_no || !config->has_so || !config->has_we
		|| !config->has_ea)
	{
		printf("Error: Missing one or more textures (NO, SO, WE, EA).\n");
		return (0);
	}
	if (!config->has_floor || !config->has_ceiling)
	{
		printf("Error: Missing floor or ceiling color.\n");
		return (0);
	}
	return (1);
}

int	parse_line(char *line, t_config *config)
{
	char	*trimmed;
	int		ret;

	ret = 1;
	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
		return (0);
	if (ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		return (1);
	}
	if (ft_strncmp(trimmed, "NO ", 3) == 0 && ft_isspace(trimmed[2]))
	{
		if (config->has_no)
			ret = 0;
		else
		{
			ret = parse_texture(trimmed, &config->no_texture);
			config->has_no = ret;
		}
	}
	else if (ft_strncmp(trimmed, "SO ", 3) == 0 && ft_isspace(trimmed[2]))
	{
		if (config->has_so)
			ret = 0;
		else
		{
			ret = parse_texture(trimmed, &config->so_texture);
			config->has_so = ret;
		}
	}
	else if (ft_strncmp(trimmed, "WE ", 3) == 0 && ft_isspace(trimmed[2]))
	{
		if (config->has_we)
			ret = 0;
		else
		{
			ret = parse_texture(trimmed, &config->we_texture);
			config->has_we = ret;
		}
	}
	else if (ft_strncmp(trimmed, "EA ", 3) == 0 && ft_isspace(trimmed[2]))
	{
		if (config->has_ea)
			ret = 0;
		else
		{
			ret = parse_texture(trimmed, &config->ea_texture);
			config->has_ea = ret;
		}
	}
	else if (ft_strncmp(trimmed, "F ", 2) == 0 && ft_isspace(trimmed[1]))
	{
		if (config->has_floor)
			ret = 0;
		else
		{
			ret = parse_floor_color(trimmed, config);
			config->has_floor = ret;
		}
	}
	else if (ft_strncmp(trimmed, "C ", 2) == 0 && ft_isspace(trimmed[1]))
	{
		if (config->has_ceiling)
			ret = 0;
		else
		{
			ret = parse_ceiling_color(trimmed, config);
			config->has_ceiling = ret;
		}
	}
	else
		ret = 0;
	free(trimmed);
	return (ret);
}

int	read_and_split_file(const char *filename, char ***lines)
{
	int		fd;
	char	*file_content;

	fd = open_cub(filename);
	file_content = read_file_content(fd);
	if (!file_content)
		return (0);
	*lines = split_lines_manual(file_content);
	free(file_content);
	if (!(*lines))
		return (0);
	return (1);
}

int	parse_textures_colors_and_map(char ***lines, t_config *config)
{
	char	**temp_lines;

	temp_lines = parse_textures_colors(*lines, config);
	if (!temp_lines)
	{
		free_split_lines(lines);
		printf("Error: Invalid texture or color specification\n");
		return (0);
	}
	*lines = temp_lines;
	temp_lines = parse_map(*lines, config);
	if (!temp_lines)
	{
		free_split_lines(lines);
		printf("Error: Invalid map configuration\n");
		return (0);
	}
	free_split_lines(lines);
	return (1);
}

int	parse_cub_file(const char *filename, t_config *config)
{
	char	**lines;

	if (!read_and_split_file(filename, &lines))
		return (0);
	if (!parse_textures_colors_and_map(&lines, config))
		return (0);
	return (1);
}

void	init_config_flags(t_config *config)
{
	if (!config)
		return ;
	config->has_no = 0;
	config->has_so = 0;
	config->has_we = 0;
	config->has_ea = 0;
	config->has_floor = 0;
	config->has_ceiling = 0;
}

int	main(int argc, char **argv)
{
	t_config	*config;

	if (argc != 2 || !has_cub_extension(argv[1]))
	{
		printf("Usage: %s <file.cub>\n", argv[0]);
		return (1);
	}
	config = (t_config *)malloc(sizeof(t_config));
	if (!config)
	{
		perror("Memory allocation failed");
		return (1);
	}
	ft_bzero(config, sizeof(t_config));
	init_config_flags(config);
	if (!parse_cub_file(argv[1], config))
	{
		free_config(config);
		free(config);
		return (1);
	}
	printf("Textures:\n");
	printf("  NO: %s\n", config->no_texture);
	printf("  SO: %s\n", config->so_texture);
	printf("  WE: %s\n", config->we_texture);
	printf("  EA: %s\n", config->ea_texture);
	printf("Colors:\n");
	printf("  Floor: %d,%d,%d\n", config->floor_color[0],
		config->floor_color[1], config->floor_color[2]);
	printf("  Ceiling: %d,%d,%d\n", config->ceiling_color[0],
		config->ceiling_color[1], config->ceiling_color[2]);
	print_map(config->map.grid, config->map.width, config->map.height);
	printf("Player position: (%.2f, %.2f), angle: %.2f radians\n",
		config->player.pos.x, config->player.pos.y, config->player.angle);
	free_config(config);
	free(config);
	return (0);
}
