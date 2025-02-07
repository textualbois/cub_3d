/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_colors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:35:18 by admin             #+#    #+#             */
/*   Updated: 2025/02/07 17:50:49 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

static int	handle_config_line(char *line, t_config *config)
{
	char	*trimmed;

	trimmed = trim_and_validate_line(line);
	if (ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		return (0);
	}
	if (!parse_line(trimmed, config))
	{
		free(trimmed);
		return (-1);
	}
	free(trimmed);
	return (1);
}

static int	process_config_lines(char **lines, t_config *config, int *index_out)
{
	int	index;
	int	valid_count;
	int	result;

	index = 0;
	valid_count = 0;
	while (lines[index] && valid_count < 6)
	{
		result = handle_config_line(lines[index], config);
		if (result == -1)
			return (-1);
		if (result == 1)
			valid_count++;
		index++;
	}
	if (valid_count < 6)
		return (-1);
	*index_out = index;
	return (0);
}

static int	count_remaining_lines(char **lines, int index)
{
	int	count;

	count = 0;
	while (lines[index + count])
		count++;
	return (count);
}

static char	**extract_remaining_lines(char **lines, int index)
{
	int		remaining_lines;
	char	**new_lines;
	int		new_index;

	remaining_lines = count_remaining_lines(lines, index);
	new_lines = malloc(sizeof(char *) * (remaining_lines + 1));
	new_index = 0;
	if (!new_lines)
		return (NULL);
	while (lines[index])
	{
		new_lines[new_index] = ft_strdup(lines[index]);
		if (!new_lines[new_index])
		{
			free_split_lines(&new_lines);
			return (NULL);
		}
		new_index++;
		index++;
	}
	new_lines[new_index] = NULL;
	return (new_lines);
}

char	**parse_textures_colors(char **lines, t_config *config)
{
	int		index;
	char	**new_lines;

	index = 0;
	if (process_config_lines(lines, config, &index) != 0)
		return (NULL);
	new_lines = extract_remaining_lines(lines, index);
	if (!new_lines)
		return (NULL);
	free_split_lines(&lines);
	return (new_lines);
}
