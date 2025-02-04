/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:26:10 by vmamoten          #+#    #+#             */
/*   Updated: 2025/02/04 23:50:23 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	error_exit(const char *msg, char **lines, int idx, t_config *config)
{
	if (msg)
		printf("Error\n%s\n", msg);
	if (lines)
		free_lines_from(lines, idx);
	if (config)
		free_config(config);
	exit(1);
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
				printf("Error\nMap contains invalid characters.\n");
				return (0);
			}
			j++;
		}
		i++;
	}
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
	if (count_players(map, config) != 1)
	{
		printf("Error\nMap must contain exactly one player.\n");
		return (0);
	}
	if (!is_player_surrounded(config))
	{
		printf("Error\nPlayer cannot be on the edge of the map.\n");
		return (0);
	}
	return (1);
}

int	skip_empty_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i] && ft_strlen(lines[i]) == 0)
		i++;
	return (i);
}

int	allocate_map_grid(t_config *config, char **lines, int i)
{
	int		j;
	int		line_length;
	int		max_width;
	char	*padded;

	config->map.height = 0;
	while (lines[i + config->map.height])
		config->map.height++;
	config->map.grid = (char **)malloc(sizeof(char *) * (config->map.height
				+ 1));
	if (!config->map.grid)
		return (0);
	max_width = 0;
	j = 0;
	while (j < config->map.height)
	{
		line_length = ft_strlen(lines[i + j]);
		if (line_length > max_width)
			max_width = line_length;
		j++;
	}
	config->map.width = max_width;
	j = 0;
	while (j < config->map.height)
	{
		padded = pad_line(lines[i + j], config->map.width);
		if (!padded)
		{
			free_lines_from(config->map.grid, 0);
			return (0);
		}
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
	if (!is_map_valid(&config->map, config))
	{
		free_lines_from(config->map.grid, 0);
		exit(1);
	}
}

int	is_valid_color_value(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	**split_color_values(char *line)
{
	char	**rgb;
	int		count;

	while (*line == ' ')
		line++;
	rgb = ft_split(line, ',');
	if (!rgb)
		return (NULL);
	count = 0;
	while (rgb[count])
		count++;
	if (count != 3)
	{
		free_lines_from(rgb, 0);
		return (NULL);
	}
	return (rgb);
}

int	convert_color_value(char *str)
{
	int		value;
	char	*trimmed_token;

	trimmed_token = ft_strtrim(str, " \t");
	if (!trimmed_token)
		return (-1);
	if (!is_valid_color_value(trimmed_token))
	{
		free(trimmed_token);
		return (-1);
	}
	value = ft_atoi(trimmed_token);
	free(trimmed_token);
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

int	validate_and_convert_color(char **rgb, int *color)
{
	int	i;
	int	value;

	i = 0;
	while (i < 3)
	{
		value = convert_color_value(rgb[i]);
		if (value == -1)
		{
			free_lines_from(rgb, 0);
			return (0);
		}
		color[i] = value;
		i++;
	}
	return (1);
}

int	parse_color(char *line, int *color)
{
	char	**rgb;

	rgb = split_color_values(line);
	if (!rgb)
		return (0);
	if (!validate_and_convert_color(rgb, color))
		return (0);
	free_lines_from(rgb, 0);
	return (1);
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

int	process_texture_or_color(char *line, char **lines, t_config *config,
		int *index)
{
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0
		|| ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
	{
		free(line);
		if (!parse_line(lines[*index], config))
		{
			free_lines_from(lines, *index);
			printf("Error\nInvalid texture or color specification\n");
			exit(1);
		}
		free(lines[*index]);
		(*index)++;
		return (1);
	}
	return (0);
}

char	*trim_and_validate_line(char *line, char **lines, int *index)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
	{
		free_lines_from(lines, *index);
		printf("Error\nMemory allocation error\n");
		exit(1);
	}
	if (ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		free(lines[*index]);
		(*index)++;
		return (NULL);
	}
	return (trimmed);
}

void	parse_textures_colors(char **lines, t_config *config, int *index)
{
	char	*temp;

	while (lines[*index])
	{
		temp = trim_and_validate_line(lines[*index], lines, index);
		if (!temp)
			continue ;
		if (!process_texture_or_color(temp, lines, config, index))
		{
			free(temp);
			break ;
		}
	}
}

int	count_lines(const char *file_content)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (file_content[i])
	{
		if (file_content[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

char	*extract_line(const char **file_content)
{
	char	*temp;
	char	*line;

	temp = ft_strchr(*file_content, '\n');
	if (temp)
	{
		line = ft_substr(*file_content, 0, temp - *file_content);
		*file_content = temp + 1;
	}
	else
	{
		line = ft_strdup(*file_content);
		*file_content += ft_strlen(*file_content);
	}
	return (line);
}

char	**split_lines_manual(const char *file_content)
{
	char	**lines;
	int		count;
	int		i;

	count = count_lines(file_content);
	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
		return (NULL);
	i = 0;
	while (*file_content)
	{
		lines[i] = extract_line(&file_content);
		if (!lines[i])
			break ;
		i++;
	}
	lines[i] = NULL;
	return (lines);
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
	lines = split_lines_manual(file_content);
	free(file_content);
	if (!lines)
		return ;
	parse_textures_colors(lines, config, &i);
	parse_map(&lines[i], config);
	free_lines_from(lines, i);
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
