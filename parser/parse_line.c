/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:07:45 by admin             #+#    #+#             */
/*   Updated: 2025/02/08 20:26:36 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_texture(char *trimmed, char **texture)
{
	char	*value;
	int		fd;

	value = ft_strtrim(trimmed + 2, " \t");
	if (!value)
		return (0);
	fd = open(value, O_RDONLY);
	if (fd < 0)
	{
		free(value);
		malloc_counter(-1, PARSER, "parsing texture value free\n");
		return (0);
	}
	close(fd);
	*texture = value;
	return (1);
}

int	handle_color_line(char *trimmed, t_config *config)
{
	int	ret;

	if (trimmed[0] == 'F')
	{
		if (config->has_floor)
			return (0);
		ret = parse_floor_color(trimmed, config);
		config->has_floor = ret;
		return (ret);
	}
	else if (trimmed[0] == 'C')
	{
		if (config->has_ceiling)
			return (0);
		ret = parse_ceiling_color(trimmed, config);
		config->has_ceiling = ret;
		return (ret);
	}
	return (0);
}

int	handle_texture_line(char *trimmed, int *has_texture, char **texture)
{
	int	ret;

	if (*has_texture)
		return (0);
	ret = parse_texture(trimmed, texture);
	*has_texture = ret;
	return (ret);
}

int	process_config_line(char *trimmed, t_config *config)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0 && ft_isspace(trimmed[2]))
		return (handle_texture_line(trimmed, &config->has_no,
				&config->no_texture));
	else if (ft_strncmp(trimmed, "SO ", 3) == 0 && ft_isspace(trimmed[2]))
		return (handle_texture_line(trimmed, &config->has_so,
				&config->so_texture));
	else if (ft_strncmp(trimmed, "WE ", 3) == 0 && ft_isspace(trimmed[2]))
		return (handle_texture_line(trimmed, &config->has_we,
				&config->we_texture));
	else if (ft_strncmp(trimmed, "EA ", 3) == 0 && ft_isspace(trimmed[2]))
		return (handle_texture_line(trimmed, &config->has_ea,
				&config->ea_texture));
	else if (ft_strncmp(trimmed, "F ", 2) == 0 && ft_isspace(trimmed[1]))
		return (handle_color_line(trimmed, config));
	else if (ft_strncmp(trimmed, "C ", 2) == 0 && ft_isspace(trimmed[1]))
		return (handle_color_line(trimmed, config));
	else
		return (0);
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
		malloc_counter(-1, PARSER, "parsing line trimmed free\n");
		return (1);
	}
	ret = process_config_line(trimmed, config);
	free(trimmed);
	malloc_counter(-1, PARSER, "parsing line trimmed free\n");
	return (ret);
}
