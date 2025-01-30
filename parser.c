/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:26:10 by admin             #+#    #+#             */
/*   Updated: 2025/01/30 17:33:32 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	read_cub_file(const char *filename)
{
	int		fd;
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("err: while open file");
		exit(1);
	}
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		write(1, buffer, bytes_read);
	}
	if (bytes_read < 0)
		perror("err: while read file");
	close(fd);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Использование: %s <file.cub>\n", argv[0]);
		return (1);
	}
	read_cub_file(argv[1]);
	return (0);
}
