/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:26:10 by admin             #+#    #+#             */
/*   Updated: 2025/01/30 22:54:51 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
//math
double	get_angle_from_char_math(char dir)
{
	if (dir == 'N')
		return (M_PI_2);
	if (dir == 'S')
		return (3 * M_PI_2);
	if (dir == 'E')
		return (0);
	if (dir == 'W')
		return (M_PI);
	return (0);
}

// mlx42 
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

void	parse_map(char **lines, t_config *config)
{
	int		i;
	int		j;
	char	c;
	int		max_width;

	max_width = 0;
	i = 0;
	while (lines[i] && ft_strlen(lines[i]) == 0)
		i++;
	config->map.height = 0;
	while (lines[i + config->map.height])
		config->map.height++;
	config->map.grid = (char **)malloc(sizeof(char *) * (config->map.height
				+ 1));
	if (!config->map.grid)
		return ;
	i = 0;
	while (i < config->map.height)
	{
		config->map.grid[i] = ft_strdup(lines[i]);
		if (!config->map.grid[i])
			return ;
		j = 0;
		while (config->map.grid[i][j])
		{
			c = config->map.grid[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				set_player_position(config, j, i, c);
				config->map.grid[i][j] = '0';
			}
			j++;
		}
		if (j > max_width)
			max_width = j;
		i++;
	}
	config->map.grid[config->map.height] = NULL;
	config->map.width = max_width;
}

int	parse_color(char *line, int *color)
{
	char	**rgb;
	int		i;

	rgb = ft_split(line, ',');
	i = 0;
	if (!rgb)
		return (0);
	while (i < 3 && rgb[i])
	{
		color[i] = ft_atoi(rgb[i]);
		free(rgb[i]);
		i++;
	}
	free(rgb);
	return (i == 3);
}

void	parse_line(char *line, t_config *config)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		config->no_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		config->so_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		config->we_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		config->ea_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(line + 2, config->floor_color);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(line + 2, config->ceiling_color);
}

void	parse_cub_file(const char *filename, t_config *config)
{
	int		fd;
	char	buffer[BUFFER_SIZE + 1];
	char	*file_content;
	int		bytes_read;
	char	*temp;
	char	**lines;
	int		i;
	int		j;

	fd = open(filename, O_RDONLY);
	file_content = NULL;
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}
	file_content = ft_strdup("");
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(file_content, buffer);
		free(file_content);
		file_content = temp;
	}
	close(fd);
	lines = ft_split(file_content, '\n');
	free(file_content);
	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		if (ft_strncmp(lines[i], "NO ", 3) == 0)
			config->no_texture = ft_strdup(lines[i] + 3);
		else if (ft_strncmp(lines[i], "SO ", 3) == 0)
			config->so_texture = ft_strdup(lines[i] + 3);
		else if (ft_strncmp(lines[i], "WE ", 3) == 0)
			config->we_texture = ft_strdup(lines[i] + 3);
		else if (ft_strncmp(lines[i], "EA ", 3) == 0)
			config->ea_texture = ft_strdup(lines[i] + 3);
		else if (ft_strncmp(lines[i], "F ", 2) == 0)
			parse_color(lines[i] + 2, config->floor_color);
		else if (ft_strncmp(lines[i], "C ", 2) == 0)
			parse_color(lines[i] + 2, config->ceiling_color);
		else
			break ;
		free(lines[i]);
		i++;
	}
	parse_map(&lines[i], config);
	j = i;
	while (lines[j])
	{
		free(lines[j]);
		j++;
	}
	free(lines);
}

void	read_cub_file(const char *filename)
{
	int		fd;
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
		write(1, buffer, bytes_read);
	if (bytes_read < 0)
		perror("Error reading file");
	close(fd);
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

	if (argc != 2)
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
