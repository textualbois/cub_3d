/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:26:10 by vmamoten          #+#    #+#             */
/*   Updated: 2025/02/02 12:32:36 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_lines_from(char **lines, int start)
{
	while (lines[start])
	{
		free(lines[start]);
		start++;
	}
	free(lines);
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

char	*pad_line(char *line, int width)
{
	char	*new_line;
	int		len;
	int		i;

	len = ft_strlen(line);
	new_line = malloc(width + 1);
	if (!new_line)
		return (NULL);
	i = 0;
	while (i < width)
	{
		if (i < len)
			new_line[i] = line[i];
		else
			new_line[i] = ' ';
		i++;
	}
	new_line[width] = '\0';
	return (new_line);
}

int	count_players(t_map *map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < ft_strlen(map->grid[i]))
		{
			if (ft_strchr("NSEW", map->grid[i][j]))
			{
				map->grid[i][j] = '0';
				count++;
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

int	is_valid_map_char(char c)
{
	const char	valid_chars[] = "01NSEW ";
	int			i;

	i = 0;
	while (valid_chars[i])
	{
		if (c == valid_chars[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_map_valid(t_map *map)
{
	if (!is_map_enclosed(map))
	{
		printf("Error\nMap is not enclosed by walls.\n");
		return (0);
	}
	if (has_invalid_spaces(map))
	{
		printf("Error\nMap contains invalid spaces.\n");
		return (0);
	}
	if (count_players(map) != 1)
	{
		printf("Error\nMap must contain exactly one player.\n");
		return (0);
	}
	return (1);
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

int	skip_empty_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i] && ft_strlen(lines[i]) == 0)
		i++;
	return (i);
}

void	process_map_row(t_config *config, int row, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr("NSEW", line[i]))
			set_player_position(config, i, row, line[i]);
		i++;
	}
	if (i > config->map.width)
		config->map.width = i;
}

int	allocate_map_grid(t_config *config, char **lines, int i)
{
	int		j;
	char	*padded;

	config->map.height = 0;
	while (lines[i + config->map.height])
		config->map.height++;
	config->map.grid = (char **)malloc(sizeof(char *) * (config->map.height
				+ 1));
	if (!config->map.grid)
		return (0);
	j = 0;
	while (j < config->map.height)
	{
		config->map.grid[j] = ft_strdup(lines[i + j]);
		if (!config->map.grid[j])
			return (0);
		process_map_row(config, j, config->map.grid[j]);
		j++;
	}
	j = 0;
	while (j < config->map.height)
	{
		padded = pad_line(config->map.grid[j], config->map.width);
		if (!padded)
			return (0);
		free(config->map.grid[j]);
		config->map.grid[j] = padded;
		j++;
	}
	config->map.grid[config->map.height] = NULL;
	return (1);
}

void	parse_map(char **lines, t_config *config)
{
	int	i;

	i = skip_empty_lines(lines);
	if (!allocate_map_grid(config, lines, i))
	{
		free_lines_from(config->map.grid, 0);
		exit(1);
	}
	if (!is_map_valid(&config->map))
	{
		free_lines_from(config->map.grid, 0);
		exit(1);
	}
}

int	parse_color(char *line, int *color)
{
	char	**rgb;
	int		i;

	while (*line == ' ')
		line++;
	rgb = ft_split(line, ',');
	if (!rgb)
		return (0);
	i = 0;
	while (i < 3 && rgb[i])
	{
		color[i] = ft_atoi(rgb[i]);
		free(rgb[i]);
		i++;
	}
	free(rgb);
	return (i == 3);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	parse_line(char *line, t_config *config)
{
	char	*trimmed;
	char	*value;

	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
		return (0);
	if (ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		return (1);
	}
	if (ft_strncmp(trimmed, "NO", 2) == 0 && ft_isspace(trimmed[2]))
	{
		value = ft_strtrim(trimmed + 2, " \t");
		config->no_texture = value;
	}
	else if (ft_strncmp(trimmed, "SO", 2) == 0 && ft_isspace(trimmed[2]))
	{
		value = ft_strtrim(trimmed + 2, " \t");
		config->so_texture = value;
	}
	else if (ft_strncmp(trimmed, "WE", 2) == 0 && ft_isspace(trimmed[2]))
	{
		value = ft_strtrim(trimmed + 2, " \t");
		config->we_texture = value;
	}
	else if (ft_strncmp(trimmed, "EA", 2) == 0 && ft_isspace(trimmed[2]))
	{
		value = ft_strtrim(trimmed + 2, " \t");
		config->ea_texture = value;
	}
	else if (ft_strncmp(trimmed, "F", 1) == 0 && ft_isspace(trimmed[1]))
	{
		value = ft_strtrim(trimmed + 1, " \t");
		if (!parse_color(value, config->floor_color))
		{
			free(value);
			free(trimmed);
			return (0);
		}
		free(value);
	}
	else if (ft_strncmp(trimmed, "C", 1) == 0 && ft_isspace(trimmed[1]))
	{
		value = ft_strtrim(trimmed + 1, " \t");
		if (!parse_color(value, config->ceiling_color))
		{
			free(value);
			free(trimmed);
			return (0);
		}
		free(value);
	}
	else
	{
		free(trimmed);
		return (0);
	}
	free(trimmed);
	return (1);
}

int	open_cub(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}
	return (fd);
}

char	*read_file_content(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*file_content;
	int		bytes_read;
	char	*temp;

	file_content = ft_strdup("");
	if (!file_content)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(file_content, buffer);
		free(file_content);
		file_content = temp;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		perror("Error reading file");
	close(fd);
	return (file_content);
}

void	parse_textures_colors(char **lines, t_config *config, int *index)
{
	while (lines[*index])
	{
		if (!parse_line(lines[*index], config))
			return ;
		free(lines[*index]);
		(*index)++;
	}
}

void	parse_cub_file(const char *filename, t_config *config)
{
	int		i;
	int		fd;
	char	*file_content;
	char	**lines;

	i = 0;
	fd = open_cub(filename);
	file_content = read_file_content(fd);
	lines = ft_split(file_content, '\n');
	free(file_content);
	if (!lines)
		return ;
	parse_textures_colors(lines, config, &i);
	parse_map(&lines[i], config);
	free_lines_from(lines, i);
}

void	print_map(t_map *map)
{
	int	i;

	i = 0;
	printf("Map (%d x %d):\n", map->width, map->height);
	while (i < map->height)
	{
		printf("%s\n", map->grid[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_config	config;

	if (argc != 2 || !has_cub_extension(argv[1]))
	{
		printf("Usage: %s <file.cub>\n", argv[0]);
		return (1);
	}
	ft_bzero(&config, sizeof(t_config));
	parse_cub_file(argv[1], &config);
	printf("Textures:\n");
	printf("  NO: %s\n", config.no_texture);
	printf("  SO: %s\n", config.so_texture);
	printf("  WE: %s\n", config.we_texture);
	printf("  EA: %s\n", config.ea_texture);
	printf("Colors:\n");
	printf("  Floor: %d,%d,%d\n", config.floor_color[0], config.floor_color[1],
		config.floor_color[2]);
	printf("  Ceiling: %d,%d,%d\n", config.ceiling_color[0],
		config.ceiling_color[1], config.ceiling_color[2]);
	print_map(&config.map);
	printf("Player position: (%.2f, %.2f), angle: %.2f radians\n",
		config.player.pos.x, config.player.pos.y, config.player.angle);
	return (0);
}
