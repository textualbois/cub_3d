/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:01:08 by admin             #+#    #+#             */
/*   Updated: 2025/02/07 14:27:59 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		malloc_counter(-1, PARSER, "parsing trimmed token free\n");
		return (-1);
	}
	value = ft_atoi(trimmed_token);
	free(trimmed_token);
	malloc_counter(-1, PARSER, "parsing trimmed token free\n");
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
			free_lines(rgb);
			return (0);
		}
		color[i] = value;
		i++;
	}
	return (1);
}
