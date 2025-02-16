/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:13:31 by admin             #+#    #+#             */
/*   Updated: 2025/02/07 14:28:47 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		free_lines(rgb);
		return (NULL);
	}
	return (rgb);
}

int	parse_color(char *line, int *color)
{
	char	**rgb;

	rgb = split_color_values(line);
	if (!rgb)
		return (0);
	if (!validate_and_convert_color(rgb, color))
		return (0);
	free_lines(rgb);
	return (1);
}

int	parse_floor_color(char *trimmed, t_config *config)
{
	char	*value;

	value = ft_strtrim(trimmed + 1, " \t");
	if (!value)
		return (0);
	if (!parse_color(value, config->floor_color))
	{
		free(value);
		malloc_counter(-1, PARSER, "parsing floor color value free\n");
		return (0);
	}
	free(value);
	malloc_counter(-1, PARSER, "parsing floor color value free\n");
	return (1);
}

int	parse_ceiling_color(char *trimmed, t_config *config)
{
	char	*value;

	value = ft_strtrim(trimmed + 1, " \t");
	if (!value)
		return (0);
	if (!parse_color(value, config->ceiling_color))
	{
		free(value);
		malloc_counter(-1, PARSER, "parsing ceiling color value free\n");
		free_config(config);
		return (0);
	}
	free(value);
	malloc_counter(-1, PARSER, "parsing ceiling color value free\n");
	return (1);
}
