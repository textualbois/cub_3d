/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:53:22 by admin             #+#    #+#             */
/*   Updated: 2025/02/07 15:57:05 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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


int	skip_empty_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i] && ft_strlen(lines[i]) == 0)
		i++;
	return (i);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}


char	*trim_and_validate_line(char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
		return (NULL);
	return (trimmed);
}
