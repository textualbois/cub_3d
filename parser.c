/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:26:10 by admin             #+#    #+#             */
/*   Updated: 2025/01/30 20:36:51 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Функция для парсинга цвета (разделение строки по ',')
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

	fd = open(filename, O_RDONLY);
	file_content = NULL;
	if (fd < 0)
	{
		perror("Ошибка открытия файла");
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
		parse_line(lines[i], config);
		free(lines[i]);
		i++;
	}
	free(lines);
}

// Функция для чтения и вывода содержимого файла
void	read_cub_file(const char *filename)
{
	int		fd;
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Ошибка открытия файла");
		exit(1);
	}
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
		write(1, buffer, bytes_read);
	if (bytes_read < 0)
		perror("Ошибка чтения файла");
	close(fd);
}

int	main(int argc, char **argv)
{
	t_config	config;

	if (argc != 2)
	{
		printf("Использование: %s <file.cub>\n", argv[0]);
		return (1);
	}
    ft_bzero(&config, sizeof(t_config));
	parse_cub_file(argv[1], &config);
	printf("Текстуры:\n");
	printf("  NO: %s\n", config.no_texture);
	printf("  SO: %s\n", config.so_texture);
	printf("  WE: %s\n", config.we_texture);
	printf("  EA: %s\n", config.ea_texture);
	printf("Цвета:\n");
	printf("  Пол: %d,%d,%d\n", config.floor_color[0], config.floor_color[1],
		config.floor_color[2]);
	printf("  Потолок: %d,%d,%d\n", config.ceiling_color[0],
		config.ceiling_color[1], config.ceiling_color[2]);
	return (0);
}
