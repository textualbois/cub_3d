/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:20:37 by admin             #+#    #+#             */
/*   Updated: 2025/02/07 15:51:10 by admin            ###   ########.fr       */
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
		file_content = temp;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		perror("Error reading file");
	close(fd);
	return (file_content);
}
