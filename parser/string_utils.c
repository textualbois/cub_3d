/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:00:16 by admin             #+#    #+#             */
/*   Updated: 2025/02/08 00:06:53 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

char	*extract_line(char **file_content)
{
	char	*line;
	char	*start;
	char	*temp;

	start = *file_content;
	temp = ft_strchr(start, '\n');
	if (temp)
	{
		line = ft_substr(start, 0, temp - start);
		*file_content = temp + 1;
	}
	else
	{
		line = ft_strdup(start);
		*file_content += ft_strlen(start);
	}
	if (!line)
		return (NULL);
	return (line);
}

void	free_split_lines(char ***lines)
{
	int	i;

	i = 0;
	if (!lines || !(*lines))
		return ;
	while ((*lines)[i])
	{
		free((*lines)[i]);
		(*lines)[i] = NULL;
		i++;
	}
	free(*lines);
	*lines = NULL;
}

char	**fill_lines_array(char **lines, char *file_content)
{
	int		i;
	char	*temp_content;

	temp_content = file_content;
	i = 0;
	while (*temp_content)
	{
		lines[i] = extract_line(&temp_content);
		if (!lines[i])
		{
			free_split_lines(&lines);
			free(file_content);
			return (NULL);
		}
		i++;
	}
	lines[i] = NULL;
	return (lines);
}

char	**split_lines_manual(char *file_content)
{
	char	**lines;
	int		count;

	if (!file_content || *file_content == '\0')
		return (NULL);
	count = count_lines(file_content);
	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
		return (NULL);
	lines = fill_lines_array(lines, file_content);
	if (!lines)
		return (NULL);
	return (lines);
}
