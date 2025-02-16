/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:20:37 by admin             #+#    #+#             */
/*   Updated: 2025/02/07 18:59:56 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		malloc_counter(-1, PARSER, "parsing file content free\n");
		file_content = temp;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		perror("Error reading file");
	close(fd);
	return (file_content);
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
	malloc_counter(-1, PARSER, "parsing file content free\n");
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
